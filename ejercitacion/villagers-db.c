//Objetivos:
//crear un programa que tome el archivo "villagers.txt" y lo copie a un archivo dat con el mismo nombre.
//En el dat se guarda una bd donde cada personaje tiene asociada su respectiva personalidad.
//una vez creado el dat, se debe poder seleccionar un personaje y se mostraran sus datos correspondientes.
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

#define MAX_VILL 30
#define BUFFERLEN 100

typedef struct{
    char name[30];
    char pers[30];
    int birthday;
    char birthmonth[10];
}villager_t;

typedef struct{
    char string[BUFFERLEN];
}buffer_t;

int txttoarray(FILE*,char*,buffer_t[]);
int parse_lines(buffer_t[],villager_t[],int);
void write_to_dat(FILE*,char*,villager_t[],int);

int main(void){
    //fn: filename
    FILE *file_v;
    FILE *f;
    char *fn_villagers="villagers.dat";
    buffer_t sbuffer[MAX_VILL];
    villager_t parsed_list[MAX_VILL];

    int index=txttoarray(f,"villagers.txt",sbuffer);
    index=parse_lines(sbuffer,parsed_list,index);
    crearArchivo(file_v,fn_villagers);
    write_to_dat(file_v,fn_villagers,parsed_list,index);

    return 0;
}

int txttoarray(FILE *archivo, char *nda, buffer_t cad[]){
    //copia las lineas del archivo de texto una por una a un array de structs
    char buffer[BUFFERLEN];
    int i=0;

    archivo=fopen(nda,"r");

    if(archivo){
        while(i<MAX_VILL && fgets(buffer,BUFFERLEN+1,archivo)){
        strcpy(cad[i].string,buffer);
        i++;
        }
        printf("\nVillager list copied.");
    }else{
        printf("\n'%s' couldn't be read.\n",nda);
    }

    fclose(archivo);

    //retorna la cantidad de lineas leidas
    return i;
    
}

int parse_lines(buffer_t original[], villager_t final[],int count){
    buffer_t aux;
    int cod;
    char *token;

    for(int i=0;i<count;i++){
        strncpy(aux.string,original[i].string,sizeof(aux.string));
        aux.string[sizeof(aux.string)-1]='\0';

        token=strtok(aux.string,",");
        if (!token) return 0;
        strncpy(final[i].name,token,sizeof(final[i].name));
        final[i].name[sizeof(final[i].name)-1]='\0';

        token=strtok(NULL,",");
        if (!token) return 0;
        strncpy(final[i].pers,token,sizeof(final[i].pers));
        final[i].pers[sizeof(final[i].pers)-1]='\0';

        token=strtok(NULL,",");
        if (!token) return 0;
        final[i].birthday=atoi(token);

        token=strtok(NULL,",");
        if (!token) return 0;
        strncpy(final[i].birthmonth,token,sizeof(final[i].birthmonth));
        final[i].birthmonth[sizeof(final[i].birthmonth)-1]='\0';

        return i;
    }

    printf("\nAll lines parsed.\n");
    
}

void write_to_dat(FILE *f, char *fn, villager_t list[], int index){
    villager_t aux;
    f=fopen(fn,"rb+");

    if(!f){
        printf("\n'%s' couldn't be read.\n",fn);
    }else{
        for(int i=0;i<index;i++){
            aux=list[i];
            fwrite(aux.name,sizeof(aux.name),1,f);
            fwrite(aux.pers,sizeof(aux.pers),1,f);
            fwrite(&aux.birthday,sizeof(int),1,f);
            fwrite(&aux.birthmonth,sizeof(aux.birthmonth),1,f);
        }
        printf("\nData writen to '%s'",fn);
    }

    fclose(f);
}



