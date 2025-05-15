#include <stdio.h>

int codigoASCII(char *);

int main(void){
    char *b="abcde";
    char c[3]={'a','b'};
    char a;
    scanf("%c",&a);

    printf("\n%c",a);
    printf("\n%s",b);
    printf("\n%s",c);

    printf("\n");

    printf("\n%d",codigoASCII(&a));
    printf("\n%d",codigoASCII(b));
    printf("\n%d",codigoASCII(c));
}

int codigoASCII(char *a){
    return (int)(*a);
}