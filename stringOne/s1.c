#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char line[1024];
	char *token = (char*) malloc(1024);
	printf("Enter a text : ");
	scanf("%[^\n]s", line);
	printf("%s\n", line);

	token = strtok(line,".");
	while(token != NULL){
		
		//strrev(token);
		printf("%s\n", token);
		token = strtok(NULL,".");
	}
	printf("\n\n");
	return EXIT_SUCCESS;
}
