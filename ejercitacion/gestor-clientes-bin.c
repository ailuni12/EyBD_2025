#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "utiles.h"

#define maxchar 19

typedef enum{
    INICIO=0,
    OPCIONUNO,
    OPCIONDOS,
    SALIDA
}menu_t;

typedef struct{
    int codigo;
    char nombre[maxchar];
    float saldo;
}cliente_t;

void cargarCliente(FILE *, char *);
void mostrarClientes(FILE *,char *);

int main(void){
    char *filename = "clientes.dat";
    FILE *archivo;
    int op=0;

    crearArchivo(archivo,filename);

    do{
        printf("\n\n||| MENU DE NAVEGACION |||\n");
        printf("\nSeleccione una opcion:");
        printf("\n[1] Registrar cliente.");
        printf("\n[2] Mostrar clientes.");
        printf("\n[3] Finalizar.");
        op=leerEntero("\nIngrese una opcion: ");

        switch(op){
        case 1:
            cargarCliente(archivo,filename);
            break;
        case 2:
            mostrarClientes(archivo,filename);
            break;
        case 3:
            printf("\nHasta luego.\n");
            break;
        default:
            printf("\nIngreso un valor invalido.\n");
            break;
        }
    }while(op!=SALIDA);

    printf("\nCantidad de registros: %d",contarRegistros(archivo,filename,sizeof(cliente_t)));

    return 0;
}

void cargarCliente(FILE *archivo, char *filename){
    int salida=1;
    cliente_t cli;
    int cantReg=contarRegistros(archivo,filename,sizeof(cliente_t));

    archivo = fopen("clientes.dat","ab");

    if(!archivo){
        printf("Error al abrir el archivo");
    }else{
        do{
            fflush(stdin);
            printf("\nIngresar nombre: ");
    
            fgets(cli.nombre,maxchar,stdin);
            limpiarNewline(cli.nombre);

            cli.codigo=cantReg++;
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

        fclose(archivo);
    }
}

void mostrarClientes(FILE *archivo, char *filename){
    cliente_t cli;

    archivo=fopen(filename,"rb");

    if(!archivo){
        printf("Error al abrir el archivo");
    }else{
        printf("\n-----DATOS REGISTRADOS-----");
        printf("\n| COD | SALDO     | NOMBRE\n");
        linea(28);

        fread(&cli,sizeof(cliente_t),1,archivo);

        //mientras que no encuentre el final del archivo
        while(!feof(archivo)){
            printf("\n| %03d | %08.2f  | %s",cli.codigo,cli.saldo,cli.nombre);
            printf("\n");
            linea(28);

            fread(&cli,sizeof(cliente_t),1,archivo); //leer proximo
        }

        fclose(archivo);
    }

}