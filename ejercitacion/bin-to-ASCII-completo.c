#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utiles.h"

#define MAX_LINE 27
#define MAX_CAD 10

int bintodec(char *);
void copiar_raw(char[][MAX_CAD]);
void printASCII(int);

int main(void){
    char raw[MAX_LINE][MAX_CAD];
    
    copiar_raw(raw);

    return 0;
}


int bintodec(char *numerobin){
    int j=0, output=0;

    //binario a decimal

    for(int i=(sizeof(numerobin)-1);i>=0;i--){
        if(numerobin[j]=='1'){
            output+=pow(2,i);
        }
        j++;
    }

    return output;
}

void copiar_raw(char raw[MAX_LINE][MAX_CAD]){
    FILE *f;
    char *fn="textoEnBinario.txt";

    f=fopen(fn,"r");

    if(!f){
        printf("Error al abrir el archivo '%s'",fn);
    }else{
        for(int i=0;i<=MAX_LINE;i++){
            fgets(raw[i],MAX_CAD,f);
            limpiarNewline(raw[i]); 
        }

        for(int i=0;i<=MAX_LINE;i++){
            printf("\n[%d]:%s",i,raw[i]);
        }
    }

    fclose(f);
}