#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct{
    char nombre[25];
    int edad;
}registro_t;

int main(void){
    char tecla;
    registro_t persona;
    FILE *archivo;
    archivo=fopen("datos.dat","rb");

    if(archivo!=NULL){
        /* Se usa lectura adelantada, de otro modo
        el último dato sale repetido */
        printf ("Muestra de registros (Nombre y Edad) de un archivo binario\n\n");
        fread(&persona,sizeof(registro_t),1,archivo);
        
            while(!feof(archivo)){
                printf("Nombre: %s, Edad: %d\n",persona.nombre, persona.edad);
                fread(&persona,sizeof(registro_t),1,archivo);
            }
        fclose(archivo);
    }else{
        printf("Error en la apertura del archivo");
    }
    
    system("pause");
    return 0;
}
