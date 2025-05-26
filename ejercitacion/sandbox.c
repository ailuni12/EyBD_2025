#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

void registro_viajes(FILE *, char *);

int main(void){
    char *nda_viajes="texto.txt";
    FILE *archivo_viajes;
    registro_viajes(archivo_viajes,nda_viajes);

    return 0;
}

void registro_viajes(FILE *archivo, char *nda){
    int c;
    char cadena[80];

    archivo=fopen(nda,"r");

    if(!archivo){
        printf("Error al abrir el archivo '%s'",nda);
    }else{
        linea(28);
        printf("\nViajes realizados:\n");
        //lee el archivo linea por linea, siempre y cuando la linea leida no sea de mayor cantidad de caracteres que el buffer (cadena[80] en este caso)
        while(fgets(cadena,81,archivo)){
            printf("\n%s",cadena);
            tecla();
        }
        fclose(archivo);
    }
}

//nota: while(fgets...) es lo mismo que fgets!=NULL