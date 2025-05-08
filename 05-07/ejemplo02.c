#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./utiles.h"
#define MAX_CLIENTES 5
#define MAX_ARTICULOS 6

typedef struct {
    int codigo;
    char nombre[20];
    float saldo;
} Cliente;

typedef struct {
    int codigo;
    char nombre[20];
    float precio;
    int stock;
    float facturado;
} Articulo;


void inicializarDatos(FILE *archClientes, FILE *archArticulos);
void mostrar_Archivos(FILE*, FILE*);
void ingresarVentas(FILE*,FILE*);
int main(){
    FILE *cli, *art;
    char *nomarchcli = "clientes.dat";
    char *nomarchart = "articulos.dat";
    cli = fopen(nomarchcli, "wb+");
    if(cli == NULL){
        printf("\n No se pudo abrir el archivo %s",nomarchcli);
    }
    art = fopen(nomarchart, "wb+");
    if(art == NULL){
        printf("\n No se pudo abrir el archivo %s",nomarchart);
    }
    inicializarDatos(cli, art);
    mostrar_Archivos(cli, art);
    linea(80);
    printf("\nA partir de ahora se arranca el ingreso de ventas\n");
    tecla();
    system("cls");
    ingresarVentas(cli, art);
    fclose(cli);
    fclose(art);
    return 0;
}


void inicializarDatos(FILE *archClientes, FILE *archArticulos) {
    Cliente clientes[MAX_CLIENTES] = {
    {1, "Lopez", 0},
    {2, "Rodriguez", 0},
    {3, "Garcia", 0},
    {4, "Martinez", 0},
    {5, "Perez", 0}
    };


    Articulo articulos[MAX_ARTICULOS] = {
    {100, "Coca Cola", 2000, 10, 0},
    {101, "Agua Tonica", 3500, 20, 0},
    {102, "Naranja Fanta", 3600, 15, 0},
    {103, "Sprite", 2800, 8, 0},
    {104, "Pomelo", 2500, 12, 0},
    {105, "Mandarina", 1500, 25, 0}
    };

    fwrite(clientes, sizeof(Cliente), MAX_CLIENTES, archClientes);
    fwrite(articulos, sizeof(Articulo), MAX_ARTICULOS, archArticulos);
}


void mostrar_Archivos(FILE *archivoCliente, FILE *archivoArticulos){

    Cliente cliente;
    rewind(archivoCliente);
    printf("\n\n Listado de clientes\n");
    linea(80);
    printf("\n");
    fread(&cliente, sizeof(cliente),1,archivoCliente); //lee el cliente y lo sobrescribe en la variable cliente, es LINEA A LINEA
    while(!feof(archivoCliente)){ //esto significa mientras no sea el fin de archivo, lo lee y muestra los clientes. si es NULL, quiere decir que no hay mas clientes
        printf("%-6d %-25s %10.2f\n",cliente.codigo, cliente.nombre, cliente.saldo); //guarda x espacios para mostrar cada dato
        fread(&cliente, sizeof(cliente),1,archivoCliente); //ACA SE LEE EL SIGUIENTE CLIENTE Y VUELVE A LA CONDICION DEL WHILE
    }

    Articulo articulo;
    rewind(archivoArticulos);
    printf("\n\n Listado de articulos\n");
    linea(80);
    printf("\n");
    fread(&articulo,sizeof(articulo),1,archivoArticulos);
    while(!feof(archivoArticulos)){
        printf("%-6d %-25s $%-10.2f %-5d %10.2f\n",articulo.codigo, articulo.nombre, articulo.precio, articulo.stock, articulo.facturado);
        fread(&articulo, sizeof(articulo), 1, archivoArticulos);
    }
}


void ingresarVentas(FILE* archivoClientes,FILE* archivoArticulos){
    rewind(archivoArticulos);
    rewind(archivoClientes);
    Cliente cliente;
    Articulo articulo;
    linea(80);
    printf("\n<< Ingreso de ventas >>\n");
    linea(80);
    int codigoCliente, codigoArticulo, clienteEncontrado = 0, articuloEncontrado = 0, cantidad, importeFacturado = 0;
    printf("\nIngrese codigo del cliente << cero o negativo >> para salir :");
    scanf("%d", &codigoCliente);
    while(codigoCliente > 0){
        fread(&cliente,sizeof(cliente),1,archivoClientes);
        while(!feof(archivoClientes) && !clienteEncontrado){
            if(codigoCliente == cliente.codigo){
                clienteEncontrado = 1;
                printf("Se encontro un cliente!!\n");
                printf("%-6d %-25s %10.2f\n",cliente.codigo, cliente.nombre, cliente.saldo);
                tecla();
                system("cls");
                printf("Ingrese un codigo de articulo: ");
                scanf("%d",&codigoArticulo);
                fread(&articulo,sizeof(articulo),1,archivoArticulos);
                while(!feof(archivoArticulos) && !articuloEncontrado){
                    if(codigoArticulo == articulo.codigo){
                        articuloEncontrado = 1;
                        printf("Se encontro un articulo!!\n");
                        printf("%-6d %-25s $%-10.2f %-5d %10.2f\n",articulo.codigo, articulo.nombre, articulo.precio, articulo.stock, articulo.facturado);
                        tecla();
                        system("cls");
                        linea(80);
                        printf("\n%-6d %-25s $%-10.2f %-5d %10.2f\n",articulo.codigo, articulo.nombre, articulo.precio, articulo.stock, articulo.facturado);
                        linea(80);
                        printf("\nIngrese la cantidad de stock: ");
                        scanf("%d",&cantidad);
                        while(cantidad < 1 || cantidad > articulo.stock){
                            printf("\nLa cantidad a facturar es negativa o supera al stock del articulo!!\n");
                            linea(80);
                            tecla();
                            system("cls");
                            linea(80);
                            printf("\n%-6d %-25s $%-10.2f %-5d %10.2f\n",articulo.codigo, articulo.nombre, articulo.precio, articulo.stock, articulo.facturado);
                            printf("\nIngrese la cantidad de stock: ");
                            scanf("%d",&cantidad);
                        }
                        importeFacturado = cantidad*articulo.precio;
                        articulo.stock -= cantidad;
                        articulo.facturado += importeFacturado;
                        cliente.saldo += importeFacturado;
                        linea(80);
                        printf("\nUsted a solicitado %d productos %s. El importe por unidad es de $%.2f. La facturacion total es de $%d",cantidad,articulo.nombre,articulo.precio,importeFacturado);
                        tecla();
                        system("cls");
                        printf("Registros actualizados!!\n");
                        mostrar_Archivos(archivoClientes,archivoArticulos);
                        tecla();
                    } else {
                        fread(&articulo,sizeof(articulo),1,archivoArticulos);
                    }

                    if(feof(archivoArticulos) && articuloEncontrado == 0){
                        rewind(archivoArticulos);
                        printf("No se encontro el articulo de codigo %d\n",codigoArticulo);
                        tecla();
                        system("cls");
                        printf("Ingrese un codigo de articulo: ");
                        scanf("%d",&codigoArticulo);
                        fread(&articulo,sizeof(articulo),1,archivoArticulos);
                    }

                }
            } else {
                fread(&cliente,sizeof(cliente),1,archivoClientes);
            }
        }

        if(clienteEncontrado == 0){
            printf("\nNo se encontro ningun cliente con el codigo %d\n",codigoCliente);
            tecla();
            system("cls");
        }
        rewind(archivoArticulos);
        rewind(archivoClientes);
        clienteEncontrado=0;
        articuloEncontrado=0;
        printf("\nIngrese codigo del cliente << cero o negativo >> para salir :");
        scanf("%d", &codigoCliente);
    }
}
