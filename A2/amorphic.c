#include<stdio.h>

int p (int b, int e){
	if(e==0) return 1;
	int r =1 ;
	while(e>0){
		r *= b;
		e--;
	}
	return r;
}

int main(){
	int n;
	printf("Enter the number : ");
	scanf("%d", &n);

	int sqn = n*n;
	int dn = 1;
	int temp = n;

	while(n>9){
		dn++;
		n/=10;
	}

	n=temp;
	int i=0,ans=0;
	while(i<dn){
		int v = sqn%10;
		sqn /= 10;
		ans += v*(p(10,i));
		i++;
	}

	if(ans == n)
		printf("YES\n");
	else printf("NO\n");

	return 0;
}
