#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

#define MAX_REGISTROS 20

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

typedef struct
{
int cod_chof;
char nom_chof[30];
int kms; // kilometros recorridos
int rec; // Recaudacion
}registro_t;

typedef struct{
    char cadena[80];
}buffer_t;

void registro_viajes(FILE *,char *);
void actualizar_bd(FILE *,char *);
void procesarRegistro(FILE *, char *, buffer_t []);

int main(void){
    char *nda_viajes="texto.txt";
    FILE *archivo_viajes;
    int op=0;


    do{
        printf("\n\n||| MENU DE NAVEGACION |||\n");
        printf("\nSeleccione una opcion:");
        printf("\n[1] Mostrar viajes realizados.");
        printf("\n[2] Mostrar choferes.");
        printf("\n[%d] Finalizar.",SALIDA);
        op=leerEntero("\nIngrese una opcion: ");

        switch(op){
        case OPCIONUNO:
            fflush(stdin);
            registro_viajes(archivo_viajes,nda_viajes);
            break;
        case OPCIONDOS:
            actualizar_bd(archivo_viajes,nda_viajes);
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

void registro_viajes(FILE *archivo, char *nda){
    char cadena[80];

    archivo=fopen(nda,"r");

    if(!archivo){
        printf("Error al abrir el archivo '%s'",nda);
    }else{
        linea(28);
        printf("\nViajes realizados:\n");
        while(fgets(cadena,81,archivo)){
            printf("%s",cadena);
        }
        printf("");
        linea(28);
    }

    fclose(archivo);
    
}

void actualizar_bd(FILE *archivo, char*nda){
    FILE *bd_choferes;
    char *nda_choferes="choferes.dat";
    registro_t buffer;
    buffer_t listado[MAX_REGISTROS];

    crearArchivo(bd_choferes,nda_choferes);
    bd_choferes=fopen(nda_choferes,"rb+");
    
    if(!bd_choferes){
        printf("Error al abrir el archivo '%s'",nda_choferes);
    }else{
        procesarRegistro(archivo,nda,listado);

        for(int i=0;i<MAX_REGISTROS;i++){
            printf("%s",listado[i].cadena);
        }
    }
}

void procesarRegistro(FILE *archivo, char *nda, buffer_t cad[]){
    char buffer[80];
    int i=0;
    while(fgets(buffer,81,archivo)){
        strcpy(cad[i].cadena,buffer);
        i++;
    }
}

