#include <stdio.h>
#include <string.h>
#include <math.h>

int p (int po){
	if(po == 0) return 1;
	int r=1;
	while(po>0){
		r *= 2;
		po--;
	}
	//printf("%d\n", ba);
	return r;
}

int main(){
	char b[16];
	printf("Enter the binary number: ");
	scanf("%s", b);
       // printf("%s\n", b);
	int d=0;
	int i;
	int j=0;
	int len = strlen(b);
	printf("%d\n", len);
	for(i=len-1;i>=0;i--){
		//printf("b[i]: %c i:  %d\n", b[i], i);
		if(b[i]== '1'){
			int temp = p(j) ;
			printf("%d\n", temp);
			d += temp;
		}
		j++;
	}
	printf("result : %d\n", d);
	return 0;
}
