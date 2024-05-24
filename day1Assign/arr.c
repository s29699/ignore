#include<stdio.h>

int main(){
	int n;
	printf("Enter the size of array : ");
	scanf("%d", &n);
	printf("\n");
	int arr[n];
	printf("Enter the array elements : ");
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i] );
	}
	printf("\n");
	for(int i=0;i<n;i++){
		printf("%d\t", arr[i] );
	}
	return 0;
}
