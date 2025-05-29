#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 20
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
/*typedef struct
{
    int numcorredor;
    float tiempo;
    char nombre[15];
    char apellido[15];

}tiempoFinal;
typedef struct
{
    int numcorredor;
    float tiempodevuelta;
    float sumatiempo;
    char nombre[15];
    char apellido[15];

}tiempoParcial;

*/

void MostrarVersion(char *aplicacion, char *circuito, char *version);
void MostrarCorredores();
void MostrarTiempos();
void MostrarPromedioTiempoVuelta(); // opción 3
void MostrarMejorTiempoVuelta(); // opción 4
void Menu();

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
        case 3: MostrarPromedioTiempoVuelta();
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
    // COMPLETAR UDS.....
    printf("OPCION 03 A DESARROLLAR\n");
    system("pause");
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
