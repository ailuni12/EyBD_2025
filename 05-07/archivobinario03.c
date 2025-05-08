#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct{
    char nombre[25];
    int edad;
}registro_t;

int main(void){
    int cantReg;
    FILE *archivo;
    archivo=fopen("datos.dat","rb");

    if(archivo!=NULL){
        fseek(archivo,0,SEEK_END);
        cantReg=ftell(archivo)/sizeof(registro_t);
        printf("\nCantidad de registros en el archivo = %d\n",cantReg);
    }else{
        printf("Error en la apertura del archivo\n");
    }

    system("pause");
    return 0;
}
