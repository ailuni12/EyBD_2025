#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define MIN_ROW 1
#define MAX_ROW 3
#define MIN_COL 1
#define MAX_COL 3
#define MAX_RAND 9999
#define MIN_RAND 1
#define MAX_CHAR 30

int numero_aleatorio (int, int);
void standby(void);
void despedida(void);
void valor_incorrecto(void);

int numero_aleatorio(int min, int max){
    return rand()%(max-min+1)+min;
}

void standby(void){
    printf("\nPresione Enter para continuar.\n");
    fflush(stdin);
    getchar();
}

void despedida(void){
    printf("\nGracias por usar la herramienta.");
    printf("\nPresione Enter para finalizar.\n");
    fflush(stdin);
    getchar();
}

void valor_incorrecto(void){
    printf("\nIngreso un valor incorrecto.");
    printf("\nIngreselo nuevamente\n");
}