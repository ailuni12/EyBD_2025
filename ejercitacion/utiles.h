#include <stdio.h>
#include <stdlib.h>
#ifndef UTILES_H_  // guardas de inclusión
#define UTILES_H_

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>

void crearArchivo(FILE *, char *);
void limpiarNewline(char *);
bool existeNewline(char *);
int codigoASCII(char *);
void imprimir_texto(FILE *, char *);
int to_int(char);

void tecla(void){
    printf("\nPresione cualquier tecla para continuar.");
    getch();
}

void linea(int x){
    int i;
    for (i = 1; i < x; i++)
        printf("-");
}

void limpiarBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void utf8(){
    #ifdef _WIN32
      system("chcp 65001 < nul");
    #endif
}

int leerEntero(const char *mensaje){
    char buffer[100];
    int numero;
    int flag = 1;

    while (flag){
        printf("%s", mensaje);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL){
            if (sscanf(buffer, "%d", &numero) == 1){
                flag = 0;
            }else{
                printf("Entrada invalida. Intente nuevamente.\n");
            }
        }
    }
    return numero;
}

//check si existe archivo binario, si no, lo crea
void crearArchivo(FILE *archivo, char *filename){
    archivo=fopen(filename,"r");

    if(!archivo){
        archivo=fopen(filename,"wb");
        if(!archivo){
            printf("\nError al crear el archivo.\n\n");
        }else{
            printf("\nSe creo '%s'.\n",filename);
        }
    }else{
        printf("\nEl archivo '%s' ya existe.\n\n",filename);
    }

    fclose(archivo);
}

void limpiarNewline(char *n){
    n[strcspn(n, "\n")] = '\0';
}

//chequear si existe newline
bool existeNewline(char *string){
    int i=0;
    while(string[i]!='\0'){
        if((string[i]=='\n')){
            return 1;
        }
        i++;
    }
    return 0;
}

int codigoASCII(char *a){
    return (int)(*a);
}

//contar registros en un archivo binario
//int elemento: sizeof del tipo de dato guardado en el archivo
int contarRegistros(FILE *archivo, char *filename, int elemento){
    int cantReg;

    archivo=fopen(filename,"rb");
    
    if(!archivo){
        printf("Error en la apertura del archivo\n");
    }else{
        fseek(archivo,0,SEEK_END);
        cantReg=ftell(archivo)/elemento;
        fclose(archivo);
    }

    return cantReg;
}

//en teoria, lee un caracter y lo convierte al int que representa
int to_int(char c){
    return c - '0';
}

//imprimir archivo de texto linea por linea
void imprimir_texto(FILE *archivo, char *nda){
    char cadena[100];

    archivo=fopen(nda,"r");

    if(!archivo){
        printf("Error al abrir el archivo '%s'",nda);
    }else{
        printf("\n---Contenido de '%s'---\n",nda);
        while(fgets(cadena,101,archivo)){
            printf("%s",cadena);
        }
        printf("\n");
        linea(23);
    }

    fclose(archivo);
    
}

#endif /* UTILES_H_ */
