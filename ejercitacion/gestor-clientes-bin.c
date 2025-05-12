#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct{
    int codigo;
    char nombre[19];
    float saldo;
}cliente_t;

void crearArchivo(FILE *, char *);
void cargarCliente(FILE *);

int main(void){
    const char *filename = "clientes.dat";
    FILE *archivo;

    crearArchivo(archivo,filename);

    return 0;
}

void crearArchivo(FILE *archivo, char filename){
    archivo=fopen(filename,"r");

    if(!archivo){
        archivo=fopen(filename,"wb");
        if(!archivo){
            printf("Error al crear el archivo.\n");
        }else{
            printf("Se creo '%s'.\n",filename);
            fclose(archivo);
        }
    }else{
        printf("El archivo '%s' ya existe.\n",filename);
        fclose(archivo);
    }

    fclose(archivo);
}

void cargarCliente(FILE *archivo){
    cliente_t cli;

    archivo = fopen("clientes.dat","wb");

    if(!archivo){
        printf("Error al abrir el archivo");
    }else{

    }
}