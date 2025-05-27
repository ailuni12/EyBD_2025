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
int parsear_lineas(buffer_t [], registro_t [],int);
bool validar_cod(registro_t [],int,int,int *);

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
    registro_t aux;

    crearArchivo(bd_choferes,nda_choferes);
    bd_choferes=fopen(nda_choferes,"rb+");
    
    if(!bd_choferes){
        printf("Error al abrir el archivo '%s'",nda_choferes);
    }else{
        int cant_registros=procesarRegistro(archivo,nda,listado);
        for(int i=0;i<cant_registros;i++){
            printf("%s",listado[i].cadena);
        }
        int index=parsear_lineas(listado,lista_final,cant_registros);

        for(int i=0;i<index;i++){
            aux=lista_final[i];
            fwrite(&aux.cod_chof,sizeof(int),1,bd_choferes);
            fwrite(aux.nom_chof,sizeof(aux.nom_chof),1,bd_choferes);
            fwrite(&aux.kms,sizeof(int),1,bd_choferes);
            fwrite(&aux.rec,sizeof(int),1,bd_choferes);
        }
    }

    fclose(bd_choferes);
}

int procesarRegistro(FILE *archivo, char *nda, buffer_t cad[]){
    //copia las lineas del archivo de texto una por una a un array de structs
    char buffer[80];
    int i=0;

    archivo=fopen(nda,"r");

    if(archivo){
        while(i<MAX_REGISTROS && fgets(buffer,81,archivo)){
        strcpy(cad[i].cadena,buffer);
        i++;
        }
    }else{
        printf("Error al leer el archivo '%s'",nda);
    }

    fclose(archivo);

    //retorna la cantidad de lineas leidas
    return i;
    
}

int parsear_lineas(buffer_t original[], registro_t final[],int cantregistros){
    buffer_t aux;
    int cod;
    char *token;
    int posicion=0;
    int index=0;

    for(int i=0;i<cantregistros;i++){
        strncpy(aux.cadena,original[i].cadena,sizeof(aux.cadena));
        aux.cadena[sizeof(aux.cadena)-1]='\0'; //asegurar que el string copiado tenga el null terminator al final, ya que strcpy no lo asegura

        // token 1: codigo
        token = strtok(aux.cadena, ",");
        if (!token) return 0; //retornar en caso de que haya error o sea NULL
        cod = atoi(token);

        if(validar_cod(final,cod,index,&posicion)){
            //saltea el token del nombre
            token = strtok(NULL, ",");
            if (!token) return 0;

            // token 3: kms
            token = strtok(NULL, ",");
            if (!token) return 0;
            final[posicion].kms=final[posicion].kms+atoi(token);

            // calcular recaudación
            final[posicion].rec=final[posicion].kms*PRECIO_KM;
        }else{
            final[index].cod_chof=cod;

            // token 2: nombre
            token = strtok(NULL, ",");
            if (!token) return 0;
            strncpy(final[index].nom_chof, token, sizeof(final[index].nom_chof));
            final[index].nom_chof[sizeof(final[index].nom_chof) - 1] = '\0';

            // token 3: kms
            token = strtok(NULL, ",");
            if (!token) return 0;
            final[index].kms = atoi(token);

            // calcular recaudación
            final[index].rec = final[index].kms*PRECIO_KM;
            index++;
        }
          
    }

    printf("\n\ncodigo |nombre |kms |recaudacion:");
    for(int j=0;j<index;j++){
        printf("\n%d| %s |%dkm|$%d",final[j].cod_chof,final[j].nom_chof,final[j].kms,final[j].rec);
    }

    return index;

}

bool validar_cod(registro_t lista[],int cod, int elementos, int *posicion){
    for(int i=0;i<elementos;i++){
        if(lista[i].cod_chof==cod){
            (*posicion)=i;
            return true;
        }
    }
    return false;
}

