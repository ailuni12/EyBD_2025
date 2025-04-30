#include <stdio.h>
#include<conio.h>

void crear(FILE *, char *);
void abrir(FILE *, char *);
void actualizar(FILE *, char *);

int main(void){
    FILE *archivo;
    char* nombre="nuevo.txt";

    crear(archivo,nombre);
    abrir(archivo,nombre);
    actualizar(archivo,nombre);

    return 0;
}

void crear(FILE *archivo, char *nombre){
    char ch;
    
    if((archivo=fopen(nombre,"w"))==NULL){
        printf("\n***El archivo %s no pudo abrirse ***\n",nombre);
    }else{
        printf("\nIngrese caracteres hasta [?]: ");
        while((ch=getchar())!='?'){
            putc(ch,archivo);
        }
        fclose(archivo);
    }
    return 0;
}

void abrir(FILE *archivo, char *nombre){
    char ch;

    if((archivo=fopen(nombre,"r"))==NULL){
        printf("\n***El archivo %s no pudo abrirse ***\n",nombre);
    }else{
        printf("\n||Archivo creado, contenido del archivo %s caracter a caracter:\n",nombre);
        while((ch=getc(archivo))!=EOF){
            printf("%c",ch);
        }
        fclose(archivo);
    }

}

void actualizar(FILE *archivo, char *nombre){
    char ch;

    if((archivo=fopen(nombre,"r+"))==NULL){
        printf("\n***El archivo %s no pudo abrirse ***\n",nombre);
    }else{
        printf("\n\n||Ingrese mas lineas hasta [?]: ");
        
        while((ch=getchar())!='?'){
            putc(ch,archivo);
        }
        
        printf("\n\n||Archivo actualizado, contenido nuevo: \n");
        
        rewind(archivo);
        while((ch=getc(archivo))!=EOF){
            printf("%c",ch);
        }
        fclose(archivo);
    }
}
