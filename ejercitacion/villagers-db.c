//Objetivos:
//crear un programa que tome el archivo "villagers.txt" y lo copie a un archivo dat con el mismo nombre.
//En el dat se guarda una bd donde cada personaje tiene asociada su respectiva personalidad.
//una vez creado el dat, se debe poder seleccionar un personaje y se mostraran sus datos correspondientes.
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

#define MAX_VILL 30

typedef enum{
    INICIO=0,
    OPCIONUNO,
    OPCIONDOS,
    OPCIONTRES,
    OPCIONCUATRO,
    OPCIONCINCO,
    OPCIONSEIS,
    OPCIONSIETE,
    SALIDA
}menu_t;

typedef struct{
    char name[30];
    char pers[30];
    int birthday;
    char birthmonth[10];
}villager_t;

typedef struct{
    char string[80];
}buffer_t;

int procesarRegistro(FILE *, char *, buffer_t []);

int main(void){
    //fn: filename
    FILE *file_v;
    char *fn_villagers="villagers.dat";

    imprimir_texto(file_v,"villagers.txt");

    return 0;
}

