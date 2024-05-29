#include <stdio.h>
#include <stdlib.h>

void duplicate(int arr[], int n){
        for(int i=0;i<n;i++){
                if(arr[i]==-1) continue;
                for(int j=i+1;j<n;j++){
                        if(arr[i]==arr[j]) arr[j] = -1;
                }
        }
}

void display(int arr[], int s){
        printf("\nArray without duplicates : ");
        for(int i=0;i<s;i++){
                if(arr[i]!=-1)
                        printf("%d ", arr[i]);
        }
        printf("\n");
}

int main(){
        int n;
        printf("Enter the array size less than 1000 : ");
        scanf("%d",&n);
        int arr[1000]={0};
        
        printf("\nEnter the array elements : ");
        
        for(int i=0;i<n;i++){
            scanf("%d",&arr[i]);
        }
        
        duplicate(arr,n);
        display(arr,n);

        return EXIT_SUCCESS;
}

