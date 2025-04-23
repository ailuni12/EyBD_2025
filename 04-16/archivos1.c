#include <stdio.h>
#include <conio.h>

int main(){
    FILE *archivo;
    char ch;
    char* nombre="txt.txt";
    if((archivo=fopen(nombre,"w"))==NULL)
    printf("No se pudo abrir '%s'",nombre);
    else{
        printf("Ingrese caracteres hasta [Enter] ");
        while((ch=getchar())!='\n')
            putc(ch,archivo);
        fclose(archivo);
    }

    return 0;
}