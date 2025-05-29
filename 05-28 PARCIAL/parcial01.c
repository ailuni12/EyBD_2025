#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utiles.h"
#define TAM 20
#define MAX 100
#define ARCH_TIEMPOS2 "tiempos2.dat"
#define ARCH_RESULTADOS "resultados2.dat"
#define ARCH_CORREDORES "corredores.dat"
#define ARCH_CONFIG "config.txt"

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
int contarcorredores();
bool validarcorredor(int [],int, int);

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
    system("pause");
    return 0;
}


void MostrarPromedioTiempoVuelta()
{
    FILE *f_corredores;
    //FILE *f_tiempos;
    char *fn_corredores="corredores.dat";
    //char *fn_tiempos="tiempos2.dat";
    //int vueltas=contarvueltas();
    int indiceCorredores=contarcorredores();
    Corredor auxc;
    //tiempos auxt;
    int input=0, i=0,indice=-1;
    int listacodigos[MAX];
    Corredor corredores[MAX];

    f_corredores=fopen(fn_corredores,"rb");

    if(!f_corredores){
        printf("El Archivo %s No pudo Abrirse!!\n",fn_corredores);
    }else{
        fread(&auxc,sizeof(auxc),1,f_corredores);
        while(!feof(f_corredores)){
            corredores[i]=auxc;
            listacodigos[i]=auxc.numcorredor;

            fread(&auxc,sizeof(auxc),1,f_corredores);
            i++;
        }

        do{
            fflush(stdin);
            input=leerEntero("\nIngrese el num de corredor: ");
            
            if(!validarcorredor(listacodigos,input,indiceCorredores)){
                printf("numero invalido");
            }
        }while(!validarcorredor(listacodigos,input,indiceCorredores));

        indice=mostrarindice(corredores,input,indiceCorredores);

        printf("%d\n",corredores[indice].numcorredor);

    }

    fclose(f_corredores);
    system("pause");


}

int contarvueltas(){
    FILE *f_corredores;
    FILE *f_tiempos;
    char *fn_corredores="corredores.dat";
    char *fn_tiempos="tiempos2.dat";
    int indiceCorredores=0;
    int numvueltas=0;

    f_corredores=fopen(fn_corredores,"rb");

    if(!f_corredores){
        printf("error");
    }else{
        indiceCorredores=contarRegistros(f_corredores,fn_corredores,sizeof(Corredor));
    }
    fclose(f_corredores);
    
    f_tiempos=fopen(fn_tiempos,"rb");

    if(!f_tiempos){
        printf("error");
    }else{
        numvueltas=contarRegistros(f_tiempos,fn_tiempos,sizeof(tiempos))/indiceCorredores;
    }

    fclose(f_tiempos);

    return numvueltas;
}

int contarcorredores(){
    FILE *f_corredores;
    char *fn_corredores="corredores.dat";
    int indiceCorredores=0;

    f_corredores=fopen(fn_corredores,"rb");

    if(!f_corredores){
        printf("error");
    }else{
        indiceCorredores=contarRegistros(f_corredores,fn_corredores,sizeof(Corredor));
    }
    fclose(f_corredores);

    return indiceCorredores;
}

bool validarcorredor(int lista[],int codigo, int indice){
    for(int i=0;i<indice;i++){
        if(lista[i]==codigo){
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

void MostrarMejorTiempoVuelta()
{
    // COMPLETAR UDS.....
    printf("OPCION 04 A DESARROLLAR\n");
    system("pause");
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

    system("cls");
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
