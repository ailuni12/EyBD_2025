#include <stdio.h>
#include <stdlib.h>
#ifndef UTILES_H_  // guardas de inclusión
#define UTILES_H_

#include <stdio.h>
#include <conio.h>

void crearArchivo(FILE *, char *);

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
                printf("Entrada inválida. Intente nuevamente.\n");
            }
        }
    }
    return numero;
}

void crearArchivo(FILE *archivo, char *filename){
    archivo=fopen(filename,"r");

    if(!archivo){
        archivo=fopen(filename,"wb");
        if(!archivo){
            printf("\nError al crear el archivo.\n\n");
        }else{
            printf("Se creo '%s'.\n",filename);
            fclose(archivo);
        }
    }else{
        printf("\nEl archivo '%s' ya existe.\n\n",filename);
        fclose(archivo);
    }

    fclose(archivo);
}

#endif /* UTILES_H_ */
