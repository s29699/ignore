#include <stdio.h>
#include "cal_proto.h"

int main(){
	int n1,n2;
	char op;

	printf("Enter the op : ");
	scanf("%c",&op);
	printf("enter the numbers : ");
	scanf("%d %d",&n1,&n2);

	switch(op){
		case '+': printf("Sum : %d\n", sum(n1,n2));
			  break;
		case '*': printf("Product : %d\n", mul(n1,n2));
			  break;
	}
	return 0;
}
