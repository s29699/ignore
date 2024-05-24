#include <stdio.h>

int main(){
    int one;
    int two;
    int res;
    printf("Enter first number: ");
    scanf("%d", &one);
    printf("Enter second  number: ");
    scanf("%d", &two);
    res = one +two;
    printf("Addition : %d + %d = %d\n", one , two, res);
    res = one-two;
    printf("Subtraction : %d - %d = %d\n", one , two, res);
    res = one* two;
    printf("Multiplication : %d * %d = %d\n", one , two, res);
    res = one / two ;
    printf("Division : %d / %d = %d\n", one , two, res);
    return 0;
}
