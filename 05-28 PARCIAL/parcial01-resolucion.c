#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utiles.h"
#define TAM 20
#define MAX 30
#define MAXTIEMPOS 230
#define ARCH_TIEMPOS2 "tiempos2.dat"
#define ARCH_RESULTADOS "resultados2.dat"
#define ARCH_CORREDORES "corredores.dat"
#define ARCH_CONFIG "config.txt"
#define F_ERROR "ERROR, no se pudo abrir "

typedef struct
{
    int numcorredor;
    char nombre[15];
    char apellido[15];
    char escuderia[15];
} Corredor;

typedef struct
{
    int numvuelta;
    int numcorredor;
    float tiempo;
} tiempos;
// ++++++++++++++++++++++++++++++++++++
// chequear posibles struct a utilizar
// ++++++++++++++++++++++++++++++++++++
typedef struct
{
    int numcorredor;
    float tiempo;
    char nombre[15];
    char apellido[15];

}tiempoFinal_t;
typedef struct
{
    int numcorredor;
    float tiempodevuelta;
    float sumatiempo;
    char nombre[15];
    char apellido[15];

}tiempoParcial_t;


void MostrarVersion(char *aplicacion, char *circuito, char *version);
void MostrarCorredores();
void MostrarTiempos();
void MostrarPromedioTiempoVuelta(); // opci�n 3
void MostrarMejorTiempoVuelta(); // opci�n 4
void Menu();
int contarvueltas();
bool validarcorredor(Corredor [],int, int);
int mostrarindice(Corredor [],int,int);
float calcularpromediovueltas(tiempos [],int,int,int);
float calcularmejorvuelta(tiempos [],int,int,int);


int main()
{
    int opcion;
    Menu();
    printf("Ingrese la opcion deseada:\n");
    scanf("%d", &opcion);

    while (opcion != -1)
    {
        switch (opcion)
        {
        case 1:
            MostrarCorredores();
            system("pause");
            break;
        case 2:
            MostrarTiempos();
            system("pause");
            break;
        case 3: 
        
                MostrarPromedioTiempoVuelta();
                break;
        case 4: MostrarMejorTiempoVuelta();
                break;
        }
        Menu();
        printf("Ingrese la opcion deseada:\n");
        scanf("%d", &opcion);
    }
    printf("\n\nsaliendo del sistema .....!!!\n\n");
    return 0;
}


void MostrarPromedioTiempoVuelta()
{
    FILE *f_corredores=fopen(ARCH_CORREDORES,"rb");
    FILE *f_tiempos=fopen(ARCH_TIEMPOS2,"rb");
    
    int indiceCorredores=contarRegistros(f_corredores,ARCH_CORREDORES,sizeof(Corredor));
    int vueltas=contarvueltas(indiceCorredores);
    
    Corredor auxc;
    tiempos auxt;
    Corredor corredores[MAX];
    tiempos listatiempos[MAXTIEMPOS];
    
    int input=0, i=0,j=0,indice=-1;

    if(!f_corredores){
        printf("%s'%s'\n",F_ERROR,ARCH_CORREDORES);
    }else{
        if(!f_tiempos){
            printf("%s'%s'\n",F_ERROR,ARCH_TIEMPOS2); 
        }else{
            while(fread(&auxc,sizeof(auxc),1,f_corredores)==1){
                corredores[i++]=auxc;
            }
            while(fread(&auxt,sizeof(auxt),1,f_tiempos)==1){
                listatiempos[j++]=auxt;
            }
            printf("Seleccione el corredor para ver sus estadisticas");
            do{
                fflush(stdin);
                input=leerEntero("\nNum de corredor: ");
                
                if(!validarcorredor(corredores,input,indiceCorredores)){
                    PNL
                    printf("Numero de corredor incorrecto");
                    PNL
                }
            }while(!validarcorredor(corredores,input,indiceCorredores));
            indice=mostrarindice(corredores,input,indiceCorredores);

            PNL
            printf("[%d] %s %s | %s",corredores[indice].numcorredor,corredores[indice].nombre,corredores[indice].apellido,corredores[indice].escuderia);
            printf("Tiempo promedio de vuelta: %.3f",calcularpromediovueltas(listatiempos,input,indiceCorredores,vueltas));
            PNL
            PNL
        }
    }

    fclose(f_corredores);
    fclose(f_tiempos);
}

int contarvueltas(int cantregistros){
    FILE *f_tiempos;
    char *fn_tiempos="tiempos2.dat";
    int numvueltas=0;
    
    f_tiempos=fopen(fn_tiempos,"rb");

    if(!f_tiempos){
        printf("error");
    }else{
        numvueltas=contarRegistros(f_tiempos,fn_tiempos,sizeof(tiempos))/cantregistros;
    }

    fclose(f_tiempos);

    return numvueltas;
}

bool validarcorredor(Corredor lista[],int codigo, int indice){
    for(int i=0;i<indice;i++){
        if(lista[i].numcorredor==codigo){
            return true;
        }
    }
    return false;
}

int mostrarindice(Corredor lista[],int codigo,int indice){
    for(int i=0;i<indice;i++){
        if(lista[i].numcorredor==codigo){
            return i;
        }
    }
    return 0;
}

float calcularpromediovueltas(tiempos t[],int input,int cantcorredores,int vueltas){
    float t_vuelta=0;
    for(int i=0;i<(cantcorredores*vueltas);i++){
        if(t[i].numcorredor==input){
            t_vuelta+=t[i].tiempo;
        }
    }
    return t_vuelta/vueltas;
}

void MostrarMejorTiempoVuelta()
{
    FILE *f_corredores=fopen(ARCH_CORREDORES,"rb");
    FILE *f_tiempos=fopen(ARCH_TIEMPOS2,"rb");
    
    int indiceCorredores=contarRegistros(f_corredores,ARCH_CORREDORES,sizeof(Corredor));
    int vueltas=contarvueltas(indiceCorredores);
    
    Corredor auxc;
    tiempos auxt;
    Corredor corredores[MAX];
    tiempos listatiempos[MAXTIEMPOS];
    
    int input=0, i=0,j=0,indice=-1;

    if(!f_corredores){
        printf("%s'%s'\n",F_ERROR,ARCH_CORREDORES);
    }else{
        if(!f_tiempos){
            printf("%s'%s'\n",F_ERROR,ARCH_TIEMPOS2); 
        }else{
            while(fread(&auxc,sizeof(auxc),1,f_corredores)==1){
                corredores[i++]=auxc;
            }
            while(fread(&auxt,sizeof(auxt),1,f_tiempos)==1){
                listatiempos[j++]=auxt;
            }
            printf("Seleccione la vuelta para ver el mejor tiempo");
            do{
                fflush(stdin);
                input=leerEntero("\nNum de vuelta: ");
                
                if(input>vueltas||input<0){
                    PNL
                    printf("Numero de vuelta incorrecto");
                    PNL
                }
            }while(input>vueltas||input<0);

            PNL
            printf("Mejor tiempo vuelta %d: %.3f",input,calcularmejorvuelta(listatiempos,input,vueltas,indiceCorredores));
            PNL
        }
    }

    fclose(f_corredores);
    fclose(f_tiempos);
}

float calcularmejorvuelta(tiempos t[],int v,int vueltas,int cantcorredores){
    float mejor=-1;
    int inicio=v*cantcorredores;
    int fin=inicio+cantcorredores-1;

    for(int i=inicio;i<fin;i++) {
        if (mejor==-1||t[i].tiempo<mejor) {
            mejor=t[i].tiempo;
        }
    }

    return mejor;
}

void mostrarVersion(char *aplicacion, char *circuito, char *version)
{
    FILE *archivo = NULL;
    archivo = fopen(ARCH_CONFIG, "r");
    if (archivo == NULL)
    {
        printf("El Archivo %s No pudo Abrirse!!\n", ARCH_CONFIG);
        printf("chequear la ruta donde se esta llamando, o si el archivo existe!!\n");
        printf("habitualmente en VS code , el archivo se encuentra en la carpeta output \n");
    }
    else
    {
        fgets(aplicacion, 15, archivo);
        puts(aplicacion);
        fgets(circuito, 15, archivo);
        puts(circuito);
        fgets(version, 5, archivo);
        puts(version);
    }
}

void Menu()
{
    char aplicacion[15];
    char circuito[15];
    char version[5];

    //system("cls");
    mostrarVersion(aplicacion, circuito, version);
    printf("-------------------------------------\n");
    printf("\t\tMENU DE OPCIONES\n");
    printf("1.Mostrar Listado de corredores.\n");
    printf("2.Mostrar el Listado de Tiempos.\n");
    printf("3.Mostrar Promedio de tiempo de vuelta por corredor .\n");
    printf("4.Mostrar mejor tiempo de una determinada vuelta.\n");
    printf("Para Salir pulsa << -1 >>.\n");
    printf("-------------------------------------\n");
}

void MostrarCorredores()
{
    Corredor aux;
    FILE *Archivo;
    Archivo = fopen("corredores.dat", "rb");
    if (Archivo != NULL)
    {
        fread(&aux, sizeof(Corredor), 1, Archivo);
        while (!feof(Archivo))
        {
            printf("Numero de Corredor:|%d| Nombre: %s. Apellido: %s. Escuderia: %s\n", aux.numcorredor, aux.nombre, aux.apellido, aux.escuderia);
            fread(&aux, sizeof(Corredor), 1, Archivo);
        }
        fclose(Archivo);
    }
    else
    {
        printf("Error en la apertura del archivo");
    }
}

void MostrarTiempos()
{
    tiempos aux;
    FILE *Archivo;
    Archivo = fopen(ARCH_TIEMPOS2, "rb");
    if (Archivo != NULL)
    {
        fread(&aux, sizeof(tiempos), 1, Archivo);
        while (!feof(Archivo))
        {
            printf("Numero de Vuelta: %d, Numero de Corredor: %d, Tiempo: %.3f\n", aux.numvuelta, aux.numcorredor, aux.tiempo);
            fread(&aux, sizeof(tiempos), 1, Archivo);
        }
        fclose(Archivo);
    }
    else
    {
        printf("Error en la apertura del archivo %s",ARCH_TIEMPOS2);
    }
}
