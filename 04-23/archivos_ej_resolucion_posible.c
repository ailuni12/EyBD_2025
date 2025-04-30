#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void escribir(FILE *);
void copiar(FILE *, FILE *);

int main(void){
    FILE *original, *copia;
    system("cls");
    fflush(stdin);

    original=fopen("original.txt","w");
    copia=fopen("copia.txt","a+");
    
    escribir(original);
    copiar(original,copia);

    return 0;
}

void escribir(FILE *orig){
    char s[81];

    printf("\nIngrese caracteres hasta [Enter] ");
    fflush(stdin);

    while(gets(s)!=NULL){
        fputs(s,orig);
        fputc('\n',orig);
    }

    printf("\nSe guardo correctamente.\n");
}

void copiar(FILE *orig, FILE *copy){
    char cad[81];

    printf("\nCOPIANDO...\n");
    while(fgets(cad,81,orig)!=NULL){
        fputs(cad,copy);
    }
    printf("Se copio correctamente.\n");
}
