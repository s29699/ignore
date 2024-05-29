#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
  char sid[100];
  float score;
};

int comp(const void* a, const void* b){
    return strcmp((*(struct Student*)a).sid , (*(struct Student*)b).sid);
};

int com(const void* a, const void* b){
    return (*(struct Student*)b).score - (*(struct Student*)a).score;
};

int main()
{
    int n;
    printf("Enter Student count: ");
    scanf("%d",&n);
    getchar();

    struct Student s1[n] ,temp[n];

    printf("Enter Id - Score\n");
    for(int i=0;i<n;i++)
        {
            char str[100];
            char *token;
            scanf(" %[^\n]",str);
            token=strtok(str,"-");

            strcpy(s1[i].sid,token);
            token=strtok(NULL," ");
            int temp=atoi(token);
            s1[i].score = (float) temp;
        }

    qsort(s1,n,sizeof(s1[0]),comp);

    for(int i=0;i<n;i++){
        if(s1[i].score == 0.0) continue;
        int j=i+1;
        float curr_sum = s1[i].score;
        while(j<n && strcmp(s1[j].sid , s1[i].sid)==0){
            curr_sum += s1[j].score;
            s1[j].score = 0.0;
            j++;
        }
        if(j-i > 1) s1[i].score = curr_sum/(j-i);
        i=j-1;
    }

    qsort(s1,n,sizeof(s1[0]),com);
    printf("\nID-Score\n");
    for(int i=0;i<n;i++){
        if(s1[i].score != 0.0)
        printf("%s-%f\n",s1[i].sid, s1[i].score);
    }


  return 0;
}

