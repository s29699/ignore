/******************************************************************************
Author: Suresh Gopal Yadav
DOC: 04-06-2024
Question: 4 length palindrome -5points, 5 length palindrome-10 points. Find total score.
*******************************************************************************/

#include <stdio.h>
#include <string.h>

int isPal(char *str, int s, int e){
    while(s<e){
        if(str[s] != str[e]) return 0;
        s++;
        e--;
    }
    return 1;
}

int main()
{
    char str[100];
    printf("Enter string size less than 100: ");
    scanf("%s",str);
    char *c = str;
    int ans = 0;
    int l = strlen(str);
    for(int i=0;i<l;i++){
        if(i+3>=l) break;
        else{
            if(isPal(c,i,i+3)==1) ans+=5;
        }
        
        if(i+4<l){
            if(isPal(c,i,i+4)==1) ans+=10;
        }
    }
    
    printf("\nTotal Value: %d\n",ans);
    return 0;
}

