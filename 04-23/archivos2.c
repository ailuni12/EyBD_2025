#include <stdio.h>

int main(void){
    FILE *archivo;
    char ch;
    char* nombre="archivo.txt";

    if((archivo=fopen(nombre,"r"))==NULL){
        printf("no se pudo abrir '%s'",nombre);
    }else{
        printf("contenido del archivo %s caracter a caracter\n",nombre);
        while((ch=getc(archivo))!=EOF){
            printf("%c",ch);
        }   
        fclose(archivo);
    }

    return 0;
}