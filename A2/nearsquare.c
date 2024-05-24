#include <stdio.h>

int main(){
	int n;
	printf("Enter a postive  number : ");
	scanf("%d", &n);
	if(n<=0){return 0;}
	int temp=1;
	while(temp*temp < n){
		if(temp*temp == n){
			printf("Number is %d\n", temp);
			return 0;
		}
		temp++;
	}
	int r = temp*temp - n;
	int l = n - (temp-1)*(temp-1);
	//printf("%d\t %d\n", r, l);
//	r -= n;
//	n -= l;	
	//printf("%d\t %d\n", r, l);
	if(r >= l){
		temp -= 1;
		printf("Answer is %d\n", temp);
	}
	else{	
		printf("Answer is %d\n", temp);
	}
	return 0;
}
