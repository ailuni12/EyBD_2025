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
    char *cadena;

    archivo=fopen(nda,"r");

    if(!archivo){
        printf("Error al abrir el archivo '%s'",nda);
    }else{
        linea(28);
        printf("\nViajes realizados:\n");
        while(!feof(archivo)){
            while((c=getc(archivo))!=EOF){
                //printf("%c",c);
                while(fgets(cadena,80,archivo)){
                    printf("\n%s\n",cadena);
                    tecla();
                } 
            }
        }

        fclose(archivo);
    }
}