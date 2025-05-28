#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define ARCH_TEXTO "viajes.txt"
#define ARCH_CHOFERES "choferes.dat"
#define COSTO 100 // Este es el costo por km (100 pesos)
typedef struct
{
    int cod_chof;
    char nom_chof[30];
    int kms;
    float rec;
} registro;

// Funciones:
void mostrarArchivoTexto();         // Muestra el archivo plano de viajes.txt
void volcarTextoABinario();         // Recordar que solo una vez se puede hacer
int menu();                         // Genera un menú para que interactue el usuario
void utf8();                        // Para ver los codigos unicode
void limpiarBuffer();
void linea(int);                    // Genera una línea de 80 asteriscos
void sacar(char x[], registro *y);  // Paso la cadena leída del archivo de texto y la estructura
void listarChoferes(char *msg);
void pausa();

int main()
{
    int op;
    utf8();
    do
    {
        op = menu();
        switch (op)
        {
        case 1:
            mostrarArchivoTexto();
            break;
        case 2:
            volcarTextoABinario();
            break;
        case 3:
            listarChoferes("Listado del archivo binario puro");

            break;
        }
    } while (op != 4);
    linea(80);
    printf(" \nSaliendo del programa !!\n");
}
//---------------------------------------------------------------------------------------------------------
void listarChoferes(char *msg)
{
    FILE *fc = fopen(ARCH_CHOFERES, "rb");
    registro temp;
    if (!fc)
    {
        printf("\nNo se pudo abrir el archivo de %s\n", ARCH_CHOFERES);
        pausa();
    }
    else
    {
        printf("\n%s\n", msg);
        while (fread(&temp, sizeof(registro), 1, fc))
        {
            printf("%4d %-30s  $%4.2f %4d\n", temp.cod_chof, temp.nom_chof, temp.rec, temp.kms);
        }
    }
    fclose(fc);
    printf("\n\n");
    pausa();
}
//---------------------------------------------------------------------------------------------------------
void mostrarArchivoTexto()
{
    FILE *ft; // puntero a archivo texto, file texto
    char cadena[81];
    if ((ft = fopen(ARCH_TEXTO, "r")) == NULL)
        printf("\n\n***El archivo %s no pudo abrirse ***\n", ARCH_TEXTO);
    else
    {
        rewind(ft);
        linea(80);                    /// Me posiciono al principio del archivo
        while (fgets(cadena, 81, ft)) //!=NULL)  hasta \n n-1 o salto de línea
            printf("%s", cadena);
        linea(80);
        fclose(ft);
    }
    printf("\n\n");
    pausa();
}
//---------------------------------------------------------------------------------------------------------
int menu()
{
    int opcion;
    system("cls");
    printf("\n Menu de opciones\n\n");
    printf("\n1.Ver archivo de texto original (texto.txt)\n");
    printf("2.Volcar archivo de texto a archivo binario consolidado (choferes.dat)\n");
    printf("3.Listar choferes plano del archivo binario\n");
    printf("4.Salir\n");
    printf("\n\nOpción: ");
    scanf("%d", &opcion);
    return opcion;
}
//---------------------------------------------------------------------------------------------------------
void volcarTextoABinario()
{
    registro chofer;
    registro aux; // Para leer del temp_fc
    char cadena[81];
    int encontrado;
    FILE *ft = NULL;
    FILE *fc_original = NULL;               // Para el archivo binario final
    FILE *fc_temp = NULL;                   // Archivo binario temporal para consolidación
    char ARCH_TEMP[] = "choferes_temp.dat"; // Nombre del archivo temporal

    printf("\n--- INICIO DE VOLCADO A BINARIO ---\n");

    // 1. Abrir el archivo de texto
    ft = fopen(ARCH_TEXTO, "r");
    if (!ft)
    {
        printf("\nError al abrir el archivo de texto: %s\n", ARCH_TEXTO);
        pausa();
        return;
    }
    printf("Archivo de texto '%s' abierto.\n", ARCH_TEXTO);

    // 2. Abrir el archivo binario TEMPORAL para escritura (lo creará o truncará si existe)
    fc_temp = fopen(ARCH_TEMP, "wb+"); // wb+ crea/trunca y permite lectura/escritura
    if (!fc_temp)
    {
        printf("\nError al crear/abrir el archivo temporal: %s.\n", ARCH_TEMP);
        fclose(ft);
        pausa();
        return;
    }
    printf("Archivo temporal '%s' creado/truncado para consolidación.\n", ARCH_TEMP);

    // 3. Leer el archivo de texto y consolidar en el archivo temporal
    rewind(ft);
    while (fgets(cadena, sizeof(cadena), ft))
    {
        // Limpiar el posible '\n' o '\r\n' que fgets pudo haber leído
        cadena[strcspn(cadena, "\r\n")] = '\0';
        sacar(cadena, &chofer); // Convierte texto a struct
        printf("\n--- Procesando línea de texto: '%s' (Chofer: %d - '%s') ---\n", cadena, chofer.cod_chof, chofer.nom_chof);

        encontrado = 0;
        rewind(fc_temp); // Ir al inicio del archivo TEMPORAL para buscar

        // Buscar en el archivo TEMPORAL
        while (fread(&aux, sizeof(registro), 1, fc_temp) == 1)
        {
            //printf("  Comparando (TEMP): actual '%d-%s' con leido '%d-%s'\n",chofer.cod_chof, chofer.nom_chof, aux.cod_chof, aux.nom_chof);

            if (aux.cod_chof == chofer.cod_chof && strcmp(aux.nom_chof, chofer.nom_chof) == 0)
            {
                // Si coincide el chofer, actualizo los valores
                aux.rec += chofer.rec;
                aux.kms += chofer.kms;
                fseek(fc_temp, -sizeof(registro), SEEK_CUR); // Vuelve un registro atrás
                fwrite(&aux, sizeof(registro), 1, fc_temp);
                encontrado = 1;
                printf("  -> Chofer %d-%s ACTUALIZADO en archivo temporal.\n", chofer.cod_chof, chofer.nom_chof);
                break; // Sale del bucle de búsqueda
            }
        }

        if (!encontrado)
        {
            // Chofer NO encontrado: lo agrega al final del archivo TEMPORAL
            fseek(fc_temp, 0, SEEK_END);
            fwrite(&chofer, sizeof(registro), 1, fc_temp);
            printf("  -> Chofer %d-%s AGREGADO al archivo temporal.\n", chofer.cod_chof, chofer.nom_chof);
        }
    }

    fclose(ft); // Cierra el archivo de texto

    // 4. Copiar el contenido consolidado del archivo temporal al archivo binario final
    printf("\nCopiando datos consolidados del temporal a '%s'.\n", ARCH_CHOFERES);
    fclose(fc_temp); // Cierra el archivo temporal para asegurarnos de que todo se escribió

    // Abrir el archivo temporal para lectura
    fc_temp = fopen(ARCH_TEMP, "rb");
    if (!fc_temp)
    {
        printf("Error reabriendo temporal para lectura.\n");
        pausa();
        return;
    }

    // Abrir el archivo final para escritura (lo creará o lo truncará a 0 bytes)
    fc_original = fopen(ARCH_CHOFERES, "wb");
    if (!fc_original)
    {
        printf("Error abriendo archivo final '%s' para escritura.\n", ARCH_CHOFERES);
        fclose(fc_temp);
        pausa();
        return;
    }

    // Leer del temporal y escribir al final
    while (fread(&aux, sizeof(registro), 1, fc_temp) == 1)
    {
        fwrite(&aux, sizeof(registro), 1, fc_original);
    }

    fclose(fc_temp);     // Cierra el temporal
    fclose(fc_original); // Cierra el archivo binario final
    remove(ARCH_TEMP);   // Elimina el archivo temporal

    printf("Volcado y consolidación al archivo binario completado con éxito.\n");
    pausa();
}
//---------------------------------------------------------------------------------------------------------
void sacar(char x[], registro *y) // Modifico el registro por dirección
{
    char *cod, *nombre, *km; //  punteros para los campos del registro, recordar que todo lo partido es devuelto como cadena

    cod = strtok(x, ",");
    y->cod_chof = atoi(cod); // Convertir a entero el codigo de chofer

    nombre = strtok(NULL, ",");
    strcpy(y->nom_chof, nombre);

    km = strtok(NULL, ",");
    y->kms = atoi(km);

    y->rec = (float)y->kms * COSTO;
}
//---------------------------------------------------------------------------------------------------------
void linea(int x)
{
    int i;
    printf("\n");
    for (i = 0; i < x - 1; i++)
        printf("*");
    printf("\n");
}
//---------------------------------------------------------------------------------------------------------
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
//---------------------------------------------------------------------------------------------------------
void utf8()
{
#ifdef _WIN32
    system("chcp 65001");
#endif
}
//---------------------------------------------------------------------------------------------------------
void pausa()
{
#ifdef _WIN32
    system("pause");
#endif
}
