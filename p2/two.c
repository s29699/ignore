/******************************************************************************
Author: Suresh Gopal Yadav
DOC: 04-06-2024
Ques: Remove the last occurence of a character from a sentence.
*******************************************************************************/

#include <stdio.h>
#include <string.h>

int main()
{
    char str[500];
    printf("Enter string size less than 100: ");
    fgets(str, 500, stdin);
    char c;
    printf("Enter the character to remove: ");
    scanf("%c",&c);
    char *ptr = str;
    
    int i=0,l = strlen(str);
    for(i=l-1;i>=0;i--){
        if(str[i]==c){
            break;
        }
    }
    
    while(i+1<l){
        str[i] = str[i+1];
        i++;
    }
    str[i]='\0';
    printf("\nFinal String is: %s\n",str);
    return 0;
}

