#include <stdio.h>

int main(){
	int n;
	printf("Enter a positive number : ");
	scanf("%d", &n);
	int ans=0;
	while(n>9){
		ans += n%10;
		n /= 10;
	}
	ans += n;
	printf("\n Sum of digits are : %d\n", ans);
       return 0;	
}
