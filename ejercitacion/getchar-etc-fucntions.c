#include <stdio.h>

int main(void){
    printf("Entrada: ");
    printf("%c",getchar());

    printf("\nEntrada: ");
    fflush(stdin);
    int c=getchar();
    printf("%c/%d",c,c);

    return 0;
}