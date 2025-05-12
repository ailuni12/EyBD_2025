#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "utiles.h"

typedef struct{
    int codigo;
    char nombre[19];
    float saldo;
}cliente_t;

void cargarCliente(FILE *);

int main(void){
    char *filename = "clientes.dat";
    FILE *archivo;

    crearArchivo(archivo,filename);

    return 0;
}

void cargarCliente(FILE *archivo){
    cliente_t cli;

    archivo = fopen("clientes.dat","wb");

    if(!archivo){
        printf("Error al abrir el archivo");
    }else{

    }
}