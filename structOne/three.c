#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product{
  char pid[100];
  int sales;
};


int comp(const void* a, const void* b){
    return strcmp((*(struct Product*)a).pid , (*(struct Product*)b).pid);
};

int com(const void* a, const void* b){
    return (*(struct Product*)b).sales - (*(struct Product*)a).sales;
};

int main()
{
    int n;
    printf("Enter total sales figure count: ");
    scanf("%d",&n);
    getchar();

    struct Product s1[n] ;

    printf("Enter pid - Sales\n");
    for(int i=0;i<n;i++)
        {
            char str[100];
            char *token;
            scanf(" %[^\n]",str);
            token=strtok(str,"-");

            strcpy(s1[i].pid,token);
            token=strtok(NULL," ");
            s1[i].sales=atoi(token);
        }

    qsort(s1,n,sizeof(s1[0]),comp);

    for(int i=0;i<n;i++){
        if(s1[i].sales == -1) continue;
        int j=i+1;
        //int curr_sum = s1[i].sales;
        while(j<n && strcmp(s1[j].pid , s1[i].pid)==0){
            s1[i].sales += s1[j].sales;
            s1[j].sales = -1;
            j++;
        }
        // if(j-i > 1) s1[i].score = curr_sum/(j-i);
        i=j-1;
    }

    qsort(s1,n,sizeof(s1[0]),com);

        printf("\nID-Score\n");
    for(int i=0;i<n;i++){
        if(s1[i].sales != -1)
        printf("%s-%d\n",s1[i].pid, s1[i].sales);
    }


  return 0;
}

