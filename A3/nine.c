#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int comp(const void* a, const void* b){
    char as[15];
    strcpy(as, (char*)a);
    char bs[15]; 
    strcpy(bs, (char*)b);
    strcmp(as,bs);
    int al = strlen(as);
    int bl = strlen(bs);
    int i=0;
    while(i<al && i<bl){
        if(as[i]>bs[i]) return 1;
        if(as[i]<bs[i]) return -1;
        i++;
    }
    if(al>bl) return 1;
    else if(al<bl) return -1;
    else return 0;
    
    //return as[0]-bs[0];
}

int main(){
    int n;
    printf("Enter the number of Strings: ");
    scanf("%d",&n);
    
    char arr[n][50] ;
    
    printf("\nEnter the strings: ");
    for(int i=0;i<n;i++){
        scanf("%s",arr[i]);
    }
    
    printf("\nAfter Sorting\n");
    for(int i=0;i<n;i++){
    qsort(arr,n,sizeof(arr[0]),comp);
            printf("%s ",arr[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

