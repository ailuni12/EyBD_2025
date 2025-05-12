#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int numero_aleatorio (int, int);
void standby(void);

typedef struct {
    uint16_t codigo;
    char nombre[50];
    uint16_t cantidad;
    float precio;
}producto_t;

typedef enum{
    INGRESO=1,
    MOSTRAR_INVENTARIO,
    CALCULAR_PRECIOS,
    BUSCAR_CODIGO,
    SALIDA
}menu_t;

int numero_aleatorio(int max, int min){
    return rand()%(max-min+1)+min;
}

void standby(void){
    printf("\nPresione Enter para continuar.\n");
    fflush(stdin);
    getchar();
}
