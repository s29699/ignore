#include <stdio.h>

int main(){
	//int arr[100]={-2};
	printf("Enter array less than size 100 : ");
	
	int s;
	scanf("%d" ,&s);
	int arr[s];
	for(int i=0;i<s;i++){
		//int temp;
		scanf("%d", &arr[i]);
		//if(temp =='\n') break;
		//s++;
		//arr[i] = temp;
	}
	/*
	for(int i=0;i<100;i++){
		if(arr[i] == -2) break;
		s++;
	}
	*/
	printf("%d\n", s);

	for(int i=0;i<s;i++){
		if(arr[i] == -1) continue;
		for(int j=i+1;j<s;j++){
			if(arr[i]==arr[j])
				arr[j] = -1;
		}
	}

	printf("Array id : ");
	for(int i=0;i<s;i++){
		if(arr[i]==-1) continue;
		
		printf("%d ", arr[i]);
	}

	printf("\n");
	return 0;
}

