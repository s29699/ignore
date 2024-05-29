#include <stdio.h>
#include <string.h>

int duplicate(char *s){
        int  r= 0;
        while(*s != '\0'){
                if(*s == '0'){*s++; continue;}
                r++;
                char *temp = s;
                *temp++;
                while(*temp != '\0'){
                        if(*temp == *s) *temp = '0';
                        *temp++;
                }
                *s++;
        }
        return r;
}

int main(){
        char s[100];
        printf("Enter the string:");
        scanf("%[^\n]s", s);
        int ol = strlen(s);

        char *temp = s;

        int len = duplicate(s);
       // printf("%d\n",len);
        char ans[len+1];
        int i=0;
        while(*temp != '\0'){
            //printf("%c\n",*temp);
                if(*temp != '0'){
                        ans[i] = *temp;
                        i++;
                }
                *temp++;
        }
        ans[len]='\0';
               
        printf("\n");
        printf("String without duplicates is: %s\n", ans);
        return 0;
}
