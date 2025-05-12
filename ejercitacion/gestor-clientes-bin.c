#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "utiles.h"

#define maxchar 19

typedef struct{
    int codigo;
    char nombre[maxchar];
    float saldo;
}cliente_t;

void cargarCliente(FILE *, char *);

int main(void){
    char *filename = "clientes.dat";
    FILE *archivo;

    crearArchivo(archivo,filename);
    cargarCliente(archivo,filename);

    printf("\nCantidad de registros: %d",contarRegistros(archivo,filename,sizeof(cliente_t)));

    return 0;
}

void cargarCliente(FILE *archivo, char *filename){
    int salida=1;
    cliente_t cli;

    archivo = fopen("clientes.dat","ab");

    if(!archivo){
        printf("Error al abrir el archivo");
    }else{
        do{
            fflush(stdin);
            printf("\nIngresar nombre: ");
    
            fgets(cli.nombre,maxchar,stdin);
            limpiarNewline(cli.nombre);

            cli.codigo=contarRegistros(archivo,filename,sizeof(cliente_t))+1;
            cli.saldo=0;

            fwrite(&cli,sizeof(cli),1,archivo);

            printf("\nSe registro el cliente correctamente.\n");

            do{
                salida=leerEntero("\nCargar otro cliente? (si-1 no-0): ");
                if(salida>1 || salida<0){
                    printf("Ingreso un valor invalido.\n");
                }
            }while(salida>1 || salida<0);

        }while(salida==1);
    }
}