#include <stdio.h>

int main(){
	int arr[1000];
	printf("Enter the size of array less than 1000 : ");
	int n;
	scanf("%d", &n);

	printf("Enter the array element : ");
	for(int i=0;i<n;i++){
		scanf("%d", &arr[i]);
	}
	
	int k;
	printf("Enter the steps to be shifted : ");
	scanf("%d", &k);

	int k = k%n;

	// findSmallPortion
	
	int small = 0,ls=0;
	if(k==n/2){ small=0; ls=n-1;}
	else if(k>n/2){ small = k; ls=k-1;}
	else{ small = 0; ls=n-1;}

	// making array of the small portion
	
	int smarr[1000];
	for(int i=0;i<=n/2;i++){
		smarr[i]=arr[small++];
	}

	// filling the small portion    
	small--;
        for(int i=0;i<k;i++){
		arr[ls] = arr[small];
		ls--;
		small--;
	}



	return 0;
}
