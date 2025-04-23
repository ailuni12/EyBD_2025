#include <stdio.h>

int contador(int);

int main(void){
    int num = 0;

    printf("Ingrese valor: ");
    scanf("%d", &num);

    int cantidad = contador(num);

    if(num <= 9){
        printf("tiene %d digito.\n", cantidad);
    } else {
        printf("tiene %d digitos.\n", cantidad);
    }

    return 0;
}

int contador(int num){
    printf("Calling contador(%d)\n", num);

    if(num <= 9){
        printf("Returning 1 (base case for %d)\n", num);
        return 1;
    } else {
        int result = 1 + contador(num / 10);
        printf("Returning %d for contador(%d)\n", result, num);
        return result;
    }
}
