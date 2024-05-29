#include <stdio.h>
#include <string.h>

int main(){
	char str[100];
	printf("Enter the string : ");
	scanf("%[^\n]s", str);

	int len = strlen(str);

	int m = len/2;

	for(int i=0;i<m;i++){
		int temp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = temp;
	}

	printf("\nReverse string is %s :", str);

	return 0;
}
