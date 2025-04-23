#include <stdio.h>

int main (void){

    int cantidad;
    int inicio = 0;
    int resultado = 0;
    printf("Ingrese la cantidad de numeros a sumar : ");
    scanf("%d", &cantidad);

    for(int x = 0; x < cantidad; x++){
        resultado += inicio + 1;
        inicio++;
    }

    printf("\nResultado: %d.", resultado);

    return 0;
}