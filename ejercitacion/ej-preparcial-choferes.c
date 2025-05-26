#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

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

void registro_viajes(FILE *,char *);
void actualizar_bd(FILE *,char *);

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
    int c;
    char *cadena;

    archivo=fopen(nda,"r");

    if(!archivo){
        printf("Error al abrir el archivo '%s'",nda);
    }else{

        linea(28);
        printf("\nViajes realizados:\n");
        while((c=getc(archivo))!=EOF){
            printf("%c",c);
            while(fgets(cadena,sizeof(cadena),archivo)){
                printf("%s",cadena);
            }
            linea(28);
        }

        fclose(archivo);
    }
}

void actualizar_bd(FILE *archivo, char*nda){
    FILE *bd_choferes;
    char *nda_choferes="choferes.dat";
    registro_t buffer;

    crearArchivo(bd_choferes,nda_choferes);
    bd_choferes=fopen(nda_choferes,"rb+");
    
    if(!bd_choferes){
        printf("Error al abrir el archivo '%s'",nda_choferes);
    }else{

    }
}

