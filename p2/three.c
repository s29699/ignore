/******************************************************************************
Author: Suresh Gopal Yadav
DOC: 04-06-2024
Ques:  Remove first occurence of character with another character.
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
    
    char cr;
    printf("Enter the character used to replace: ");
    scanf(" %c",&cr);
    
    int l = strlen(str);
    for(int i=0;i<l;i++){
        if(str[i]==c){
            str[i]=cr;
            break;
        }
    }
    
    printf("\n\nFinal String is: %s\n",str);
    return 0;
}

