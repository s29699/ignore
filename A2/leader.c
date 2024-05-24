#include <stdio.h>

int main(){
	printf("Enter the size of array : ");
	int n;
	scanf("%d", &n);

	int arr[n];
	printf("enter the array element : ");
	for(int i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}

	int curr_end = arr[n-1];
	for(int i=n-2;i>=0;i--){
		if(arr[i]>curr_end) curr_end = arr[i];
		else arr[i] = -1;
	}

	printf("Leader elements are : ");
	for(int i=0;i<n;i++)
		if(arr[i] != -1) printf("%d ", arr[i]);
printf("\n");
return 0;	
}
