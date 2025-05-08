#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct{
    char nombre[25];
    int edad;
}registro_t;

void cargarRegistro(FILE *);
void muestraRegistro(FILE *);
void contarRegistros(FILE *);

int main(void){
    FILE *archivo;
    
    cargarRegistro(archivo);
    muestraRegistro(archivo);
    contarRegistros(archivo);

    return 0;
}

void cargarRegistro(FILE *archivo){
    char tecla;
    registro_t persona;

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

            if(tecla!='s'){
                fclose(archivo);
            }
        }while (tecla=='s');

    }else{
        printf("Error en la apertura del archivo");
    }

    system("pause");
}

void muestraRegistro(FILE *archivo){
    char tecla;
    int mayores=0;
    registro_t persona;

    archivo=fopen("datos.dat","rb");

    if(archivo!=NULL){
        /* Se usa lectura adelantada, de otro modo
        el último dato sale repetido */
        printf ("Muestra de registros (Nombre y Edad) de un archivo binario\n\n");

        fread(&persona,sizeof(registro_t),1,archivo);
        //&persona -> buffer donde guarda los datos
        //sizeof(registro_t) -> tamanio de un registro del buffer/archivo
        //1 -> cant de registros a leer
        //archivo -> origen

            while(!feof(archivo)){
                //mientras que no encuentre el fin del archivo, imprime el registro leido
                printf("Nombre: %s, Edad: %d\n",persona.nombre, persona.edad);
                if(persona.edad>=18){
                    mayores++;
                }
                fread(&persona,sizeof(registro_t),1,archivo); //lee el siguiente registro
            }
        printf("\nMayores de edad: %d\n",mayores);
        fclose(archivo);
    }else{
        printf("Error en la apertura del archivo");
    }
    
    system("pause");
}

void contarRegistros(FILE *archivo){
    int cantReg;

    archivo=fopen("datos.dat","rb");
    
    if(archivo!=NULL){
        fseek(archivo,0,SEEK_END);
        cantReg=ftell(archivo)/sizeof(registro_t);
        printf("\nCantidad de registros en el archivo = %d\n",cantReg);
    }else{
        printf("Error en la apertura del archivo\n");
    }

    system("pause");
}