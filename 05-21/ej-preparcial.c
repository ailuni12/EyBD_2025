#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

typedef enum{
    INICIO=0,
    OPCIONUNO,
    SALIDA
}menu_t;

typedef struct
{
int cod_chof;
char nom_chof[30];
int kms; // kilometros recorridos
int rec; // Recaudaci�n
}registro_t;

void actualizarRegistros();

int main(void){
    int op=0;


    do{
        printf("\n\n||| MENU DE NAVEGACION |||\n");
        printf("\nSeleccione una opcion:");
        printf("\n[1] Mostrar choferes.");
        printf("\n[2] Finalizar.");
        op=leerEntero("\nIngrese una opcion: ");

        switch(op){
        case OPCIONUNO:
            fflush(stdin);
            actualizarRegistros();
            break;
        case SALIDA:
            printf("\nHasta luego.\n");
            break;
        default:
            printf("\nIngreso un valor invalido.\n");
            break;
        }
    }while(op!=SALIDA);

    return 0;
}

void actualizarRegistros(){
    int c;
    char cadena[100];
    char *nda_viajes="texto.txt";
    FILE *archivo_viajes;

    archivo_viajes=fopen(nda_viajes,"r");

    if(!archivo_viajes){
        printf("Error al abrir el archivo");
    }else{

        while((c = getc(archivo_viajes))!=EOF){
            printf("%c",c);
            while(fgets(cadena,100,archivo_viajes)) // Almacena en un cadena !=NULL) hasta \n n-1 o salto de linea
            printf("%s",cadena);
            printf("\n\n****\n");
        }

        fclose(archivo_viajes);
    }
}

