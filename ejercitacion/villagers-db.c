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

int txttoarray(FILE*,char*,buffer_t[]);
int parse_lines(buffer_t[],villager_t[],int);
void write_to_dat(FILE*,char*,villager_t[],int);
void list_villagers(FILE*,char*);
void display_one_v(FILE*,char*,int);

int main(void){
    //fn: filename
    FILE *file_v;
    FILE *f;
    char *fn_villagers="villagers.dat";
    buffer_t sbuffer[MAX_VILL];
    villager_t parsed_list[MAX_VILL];
    int op=0;
    int index=0;
    int input=0;
    
    if(!existe(file_v,fn_villagers)){
        index=txttoarray(f,"villagers.txt",sbuffer);
        index=parse_lines(sbuffer,parsed_list,index);
        crearArchivo(file_v,fn_villagers);
        write_to_dat(file_v,fn_villagers,parsed_list,index);
    }
    index=contarRegistros(file_v,fn_villagers,sizeof(villager_t));
    
    do{
        printf("\n\n||| NAVIGATION MENU |||\n");
        printf("\nSelect an option:");
        printf("\n[1] List all Villagers.");
        printf("\n[2] Show one villager.");
        printf("\n[%d] Finalizar.",SALIDA);
        op=leerEntero("\nOption: ");

        switch(op){
        case OPCIONUNO:
            fflush(stdin);
            list_villagers(file_v,fn_villagers);
            break;
        case OPCIONDOS:
            printf("\nNumber of registered villagers: %d\n",index);
            do{
                input=leerEntero("Select a villager number: ");
                if(input>index||input<0) printf("\nError. Type again.");
            }while(input>index||input<0);
            display_one_v(file_v, fn_villagers, input-1);
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

int parse_lines(buffer_t raw[], villager_t parsed[],int count){
    buffer_t aux;
    char *token;

    for(int i=0;i<count;i++){
        strncpy(aux.string,raw[i].string,sizeof(aux.string));
        aux.string[sizeof(aux.string)-1]='\0';

        token=strtok(aux.string,",");
        if (!token) return 0;
        strncpy(parsed[i].name,token,sizeof(parsed[i].name));
        parsed[i].name[sizeof(parsed[i].name)-1]='\0';

        token=strtok(NULL,",");
        if (!token) return 0;
        strncpy(parsed[i].pers,token,sizeof(parsed[i].pers));
        parsed[i].pers[sizeof(parsed[i].pers)-1]='\0';

        token=strtok(NULL,",");
        if (!token) return 0;
        parsed[i].birthday=atoi(token);

        token=strtok(NULL,".");
        if (!token) return 0;
        strncpy(parsed[i].birthmonth,token,sizeof(parsed[i].birthmonth));
        parsed[i].birthmonth[sizeof(parsed[i].birthmonth)-1]='\0';
    }

    printf("\nAll lines parsed.\n");
    return count;
}

void write_to_dat(FILE *f, char *fn, villager_t list[], int index){
    f=fopen(fn,"wb");

    if(!f){
        printf("\n'%s' couldn't be read.\n",fn);
    }else{
        for(int i=0;i<index;i++){
            fwrite(&list[i], sizeof(villager_t),1,f);
        }
        printf("\nData writen to '%s'",fn);
    }

    fclose(f);
}

void list_villagers(FILE *f,char *fn){
    villager_t v;
    f=fopen(fn,"rb");

    if(!f){
        printf("\n'%s' couldn't be read.\n",fn);
    }else{
        
        printf("\nVILLAGER LIST:\n");
        linea(20);
        fread(&v,sizeof(v),1,f);
        
        while(!feof(f)){
            printf("\nName: %s\nPersonality: %s\nBirthday: %s %d\n",v.name,v.pers,v.birthmonth,v.birthday);
            linea(20);

            fread(&v,sizeof(v),1,f);
        }
    }

}

void display_one_v(FILE *f,char *fn,int input){
    villager_t v;
    f=fopen(fn,"rb");

    if(!f){
        printf("\n'%s' couldn't be read.\n",fn);
    }else{
        fseek(f,sizeof(villager_t)*input,SEEK_SET);
        fread(&v,sizeof(villager_t),1,f);
        printf("\nVILLAGER INFO:\n");
        printf("\nName: %s\nPersonality: %s\nBirthday: %s %d\n",v.name,v.pers,v.birthmonth,v.birthday);
        linea(20);
    }

    fclose(f);
}


