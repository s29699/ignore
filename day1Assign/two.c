#include <stdio.h>

int main(){
	int first;
	int second;
	char op;
	printf("Enter first number: ");
	scanf("%d", &first);
	printf("Enter second  number: ");
	scanf("%d", &second);
	printf("Enter any of four + ,- , *, /  : ");
	scanf(" %c", &op);
	if(op == '+'){
		printf("result of add: %d",first + second);
	}else if(op == '-'){
		printf("result of sub: %d",first - second);
	}else if(op == '*'){
		printf("result of multiplication: %d",first * second);
	}else if(op == '/'){
		printf("result of division: %d",first / second);
	}
	printf("\n");
	return 0;
}
