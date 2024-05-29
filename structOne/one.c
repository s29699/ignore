#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Sales{
  char P_id[100];
  int rate;
  int flag;
};

int comp(const void* a, const void* b){
    struct Sales f = *(struct Sales*)a;
    struct Sales s = *(struct Sales*)b;
    
    return s.rate - f.rate ;
};


int main()
{
    int n;
    printf("Enter sales count: ");
    scanf("%d",&n);
    getchar();
    
    struct Sales s1[n] ,temp[n];
    
    printf("Enter Product_Id - Sales_amount\n");
    for(int i=0;i<n;i++)
        {
            char str[100];
            char *token;
            scanf(" %[^\n]",str);
            token=strtok(str,"-");
            
            strcpy(s1[i].P_id,token);
            token=strtok(NULL," ");
            s1[i].rate=atoi(token);
            s1[i].flag=0;
        }
        
    qsort(s1,n,sizeof(s1[0]),comp);
    
    for(int i=0;i<n;i++){
        if(s1[i].flag == -1) continue;
        int max = s1[i].rate;
        int prev = i;
        for(int j=i+1;j<n;j++){
            if(strcmp(s1[i].P_id,s1[j].P_id)==0){
                if(s1[j].rate > max){
                    s1[prev].flag = -1;
                    max = s1[j].rate;
                    prev = j;
                }
                else{
                    s1[j].flag = -1;
                }
            }
        }
    }
    printf("\nProduct_ID-Total_sales_amount\n");
    for(int i=0;i<n;i++){
        if(s1[i].flag != -1)
        printf("%s-%d\n",s1[i].P_id, s1[i].rate);
    }
    
    
  return 0;  
}

