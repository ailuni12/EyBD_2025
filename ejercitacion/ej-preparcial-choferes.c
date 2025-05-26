#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

#define MAX_REGISTROS 20
#define PRECIO_KM 2000

typedef enum{
    INICIO=0,
    OPCIONUNO,
    OPCIONDOS,
    OPCIONTRES,
    OPCIONCUATRO,
    OPCIONCINCO,
    OPCIONSEIS,
    OPCIONSIETE,
    SALIDA
}menu_t;

typedef struct
{
int cod_chof;
char nom_chof[30];
int kms; // kilometros recorridos
int rec; // Recaudacion
}registro_t;

typedef struct{
    char cadena[80];
}buffer_t;

void registro_viajes(FILE *,char *);
void actualizar_bd(FILE *,char *);
int procesarRegistro(FILE *, char *, buffer_t []);
bool validar_cod(registro_t [],int,int);

int main(void){
    char *nda_viajes="texto.txt";
    FILE *archivo_viajes;
    int op=0;


    do{
        printf("\n\n||| MENU DE NAVEGACION |||\n");
        printf("\nSeleccione una opcion:");
        printf("\n[1] Mostrar viajes realizados.");
        printf("\n[2] Mostrar choferes.");
        printf("\n[%d] Finalizar.",SALIDA);
        op=leerEntero("\nIngrese una opcion: ");

        switch(op){
        case OPCIONUNO:
            fflush(stdin);
            registro_viajes(archivo_viajes,nda_viajes);
            break;
        case OPCIONDOS:
            actualizar_bd(archivo_viajes,nda_viajes);
            break;
        case SALIDA:
            printf("\nHasta luego.\n");
            break;
        default:
            printf("\nIngreso un valor invalido.\n");
            break;
        }
    }while(op!=SALIDA);

    return 0;
}

void registro_viajes(FILE *archivo, char *nda){
    char cadena[80];

    archivo=fopen(nda,"r");

    if(!archivo){
        printf("Error al abrir el archivo '%s'",nda);
    }else{
        linea(28);
        printf("\nViajes realizados:\n");
        while(fgets(cadena,81,archivo)){
            printf("%s",cadena);
        }
        printf("");
        linea(28);
    }

    fclose(archivo);
    
}

void actualizar_bd(FILE *archivo, char*nda){
    FILE *bd_choferes;
    char *nda_choferes="choferes.dat";
    buffer_t listado[MAX_REGISTROS];
    registro_t lista_final[MAX_REGISTROS];

    crearArchivo(bd_choferes,nda_choferes);
    bd_choferes=fopen(nda_choferes,"rb+");
    
    if(!bd_choferes){
        printf("Error al abrir el archivo '%s'",nda_choferes);
    }else{
        int cant_registros=procesarRegistro(archivo,nda,listado);
        parsear_lineas(listado,lista_final,cant_registros);
    }

    fclose(bd_choferes);
}

int procesarRegistro(FILE *archivo, char *nda, buffer_t cad[]){
    //copia las lineas del archivo de texto una por una a un array de structs
    char buffer[80];
    int i=0;

    archivo=fopen(nda,"r");

    if(archivo){
        while(i<MAX_REGISTROS && (buffer,81,archivo)){
        strcpy(cad[i].cadena,buffer);
        i++;
        }
    }else{
        printf("Error al leer el archivo '%s'",nda);
    }

    fclose(archivo);

    return i;
    
}

int parsear_lineas(buffer_t original[], registro_t final[],int cantregistros){
    buffer_t aux;
    int cod;
    char *token;

    for(int i=0;i<cantregistros;i++){
        strncpy(aux.cadena,original[i].cadena,sizeof(aux.cadena));
        aux.cadena[sizeof(aux.cadena)-1]='\0'; //asegurar que el string copiado tenga el null terminator al final, ya que strcpy no lo asegura

        // token 1: codigo
        token = strtok(aux.cadena, ",");
        if (!token) return 0; //retornar en caso de que haya error o sea NULL
        cod = atoi(token);

        if(validar_cod(final,cod,i)){
            // token 3: kms
            token = strtok(NULL, ",");
            if (!token) return 0;
            final[i].kms += atoi(token);

            // calcular recaudación
            final[i].rec = final[i].kms*PRECIO_KM;
        }else{
            final[i].cod_chof=cod;

            // token 2: nombre
            token = strtok(NULL, ",");
            if (!token) return 0;
            strncpy(final[i].nom_chof, token, sizeof(final[i].nom_chof));
            final[i].nom_chof[sizeof(final[i].nom_chof) - 1] = '\0';

            // token 3: kms
            token = strtok(NULL, ",");
            if (!token) return 0;
            final[i].kms = atoi(token);

            // calcular recaudación
            final[i].rec = final[i].kms*PRECIO_KM;
        }
          
    }

    printf("\ncodigo|nombre|kms|recaudacion:\n");
    for(int j=0;j<cantregistros;j++){
        printf("%d|%s|%d|%f",final[j].cod_chof,final[j].nom_chof,final[j].kms,final[j].rec);
    }

    return 1;

}

bool validar_cod(registro_t lista[],int cod, int elementos){
    for(int i=0;i<elementos;i++){
        if(lista[i].cod_chof==cod) return true;
    }
    return false;
}

