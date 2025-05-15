#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utiles.h"

#define maxchar 30

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

typedef struct{
    int codigo;
    char nombre[maxchar];
    float saldo;
}cliente_t;

typedef struct{
    int art_cod;
    char articulo[maxchar];
    float precio_uni;
    int stock;
    float total_facturado;
}articulo_t;

typedef struct{
    //Código de cliente
    //Código de artículo
    int cantidad;//Cantidad
    float total;//Importe total de la operación
}factura_t;

void cargarCliente(FILE *, char *);
void mostrarClientes(FILE *,char *);
void cargarArticulo(FILE *,char *);
void mostrarArticulos(FILE *, char *);
void ordenarNombres(FILE *, char *);

int main(void){
    //nda = 'Nombre de Archivo'
    char *nda_clientes = "clientes.dat"; 
    char *nda_articulos= "articulos.dat";
    char *nda_facturas= "facturas.dat";
    FILE *archivo_clientes;
    FILE *archivo_articulos;
    FILE *archivo_facturas;
    int op=0;

    crearArchivo(archivo_clientes,nda_clientes);
    crearArchivo(archivo_articulos,nda_articulos);
    crearArchivo(archivo_facturas,nda_facturas);

    do{
        printf("\n\n||| MENU DE NAVEGACION |||\n");
        printf("\nSeleccione una opcion:");
        printf("\n[1] Mostrar clientes.");
        printf("\n[2] Mostrar articulos.");
        printf("\n[3] Agregar cliente.");
        printf("\n[4] Agregar articulo.");
        printf("\n[5] Crear factura.");
        printf("\n[6] Ranking ventas por articulo.");
        printf("\n[7] Listar clientes por nombre.");
        printf("\n[8] Finalizar.");
        op=leerEntero("\nIngrese una opcion: ");

        switch(op){
        case OPCIONUNO:
            mostrarClientes(archivo_clientes,nda_clientes);
            break;
        case OPCIONDOS:
            mostrarArticulos(archivo_articulos,nda_articulos);
            break;
        case OPCIONTRES:
            cargarCliente(archivo_clientes,nda_clientes);
            break;
        case OPCIONCUATRO:
            cargarArticulo(archivo_articulos,nda_articulos);
            break;
        case OPCIONCINCO:
            break;
        case OPCIONSEIS:
            break;
        case OPCIONSIETE:
            break;
        case SALIDA:
            printf("\nHasta luego.\n");
            break;
        default:
            printf("\nIngreso un valor invalido.\n");
            break;
        }
    }while(op!=SALIDA);

    printf("\nCantidad de registros: %d",contarRegistros(archivo_clientes,nda_clientes,sizeof(cliente_t)));

    return 0;
}

void cargarCliente(FILE *archivo_clientes, char *nda_clientes){
    int salida=1;
    cliente_t cli;
    int cantReg=contarRegistros(archivo_clientes,nda_clientes,sizeof(cliente_t));

    archivo_clientes = fopen("clientes.dat","ab");

    if(!archivo_clientes){
        printf("Error al abrir el Archivo");
    }else{
        do{
            fflush(stdin);
            printf("\nIngresar nombre: ");
    
            fgets(cli.nombre,maxchar,stdin);
            limpiarNewline(cli.nombre);

            cli.codigo=cantReg++;
            cli.saldo=0;

            fwrite(&cli,sizeof(cli),1,archivo_clientes);

            printf("\nSe registro el cliente correctamente.\n");

            do{
                salida=leerEntero("\nCargar otro cliente? (si-1 no-0): ");
                if(salida>1 || salida<0){
                    printf("Ingreso un valor invalido.\n");
                }
            }while(salida>1 || salida<0);

        }while(salida==1);

        fclose(archivo_clientes);
    }

    tecla();
}

void cargarArticulo(FILE *archivo_articulos,char *nda_articulos){
    int salida=1;
    articulo_t art;
    int cantReg=contarRegistros(archivo_articulos,nda_articulos,sizeof(articulo_t));

    archivo_articulos = fopen(nda_articulos,"ab");

    if(!archivo_articulos){
        printf("Error al abrir el Archivo");
    }else{
        do{
            fflush(stdin);
            printf("\nIngresar Articulo: ");

            fgets(art.articulo,maxchar,stdin);
            limpiarNewline(art.articulo);

            fflush(stdin);
            do{
                printf("\nIngresar Precio: ");
                scanf("%f",&art.precio_uni);
                if(art.precio_uni<0){
                    printf("Ingreso un valor invalido.\n");
                }
            }while(art.precio_uni<0);
            
            fflush(stdin);
            do{
                art.stock=leerEntero("\nIngresar Stock: ");
                if(art.stock>99 || art.stock<0){
                    printf("Ingreso un valor invalido.\n");
                }
            }while(art.stock>99 || art.stock<0);

            art.art_cod=cantReg++;
            art.total_facturado=0;

            fwrite(&art,sizeof(art),1,archivo_articulos);

            printf("\nSe registro el Articulo correctamente.\n");

            do{
                salida=leerEntero("\nCargar otro Articulo? (si-1 no-0): ");
                if(salida>1 || salida<0){
                    printf("Ingreso un valor invalido.\n");
                }
            }while(salida>1 || salida<0);

        }while(salida==1);

        fclose(archivo_articulos);
    }

    tecla();
}

void mostrarClientes(FILE *archivo_clientes, char *nda_clientes){
    cliente_t cli;

    archivo_clientes=fopen(nda_clientes,"rb");

    if(!archivo_clientes){
        printf("Error al abrir el Archivo");
    }else{
        printf("\n-----DATOS REGISTRADOS-----");
        printf("\n| COD | SALDO     | NOMBRE\n");
        linea(28);

        fread(&cli,sizeof(cliente_t),1,archivo_clientes);

        //mientras que no encuentre el final del Archivo
        while(!feof(archivo_clientes)){
            printf("\n| %03d | %08.2f  | %s",cli.codigo,cli.saldo,cli.nombre);
            printf("\n");
            linea(28);

            fread(&cli,sizeof(cliente_t),1,archivo_clientes); //leer proximo
        }

        fclose(archivo_clientes);
    }

    tecla();

}

void mostrarArticulos(FILE *archivo_articulos, char *nda_articulos){
    articulo_t art;

    archivo_articulos=fopen(nda_articulos,"rb");

    if(!archivo_articulos){
        printf("Error al abrir el Archivo");
    }else{
        printf("\n--------INVENTARIO DE ARTICULOS--------");
        printf("\n| COD | STOCK | PRECIO    | ARTICULO \n");
        linea(40);

        fread(&art,sizeof(articulo_t),1,archivo_articulos);

        //mientras que no encuentre el final del Archivo
        while(!feof(archivo_articulos)){
            printf("\n| %03d | %05d | %08.2f  | %s",art.art_cod,art.stock,art.precio_uni,art.articulo);
            printf("\n");
            linea(40);

            fread(&art,sizeof(articulo_t),1,archivo_articulos); //leer proximo
        }

        fclose(archivo_articulos);
    }

    tecla();

}

void ordenarNombres(FILE *archivo_clientes, char *nda_clientes){

}