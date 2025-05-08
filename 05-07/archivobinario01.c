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
    archivo=fopen("datos.dat","ab");

    if(archivo!=NULL){
        do{
            fflush(stdin); /* Se vacía el buffer de teclado */
            printf("\nIntroduzca el nombre de la persona: ");
            scanf("%s",persona.nombre);

                if(strlen(persona.nombre)>0){
                    printf("Introduzca la edad: ");
                    scanf("%d",&(persona.edad));
                    fwrite(&persona,sizeof(persona),1,archivo);
                    //parametros: Dir de la variable, tamaño del dato
                    // (en este caso del STRUCT), el 1 es que voy a escribir un solo registro, en archivo
                    printf ("\n");
                }

            printf ("Desea continuar (s/n): ");
            fflush (stdin);
            tecla = getchar ();
        }while (tecla=='s');

    }else{
        printf("Error en la apertura del archivo");
    }

    system("pause");

}
