#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "herramientas.h"
#include "estructuras.h"

#define min_cod 1
#define max_cod 9999
#define max_edad 110
#define min_edad 18
#define max_nota 10
#define min_nota 1

void menu(alumno_t [][MAX_COL]);
void inicializar_lista(alumno_t [][MAX_COL]);
void registrar_alumno(alumno_t [][MAX_COL]);
void mostrar_lista(alumno_t [][MAX_COL]);
void ordenar_por_edad(alumno_t [][MAX_COL]);
bool validar_codigo(alumno_t [][MAX_COL],int);
bool validar_lugar(alumno_t [][MAX_COL],int,int);

int main(void){
    alumno_t alumnos[MAX_ROW][MAX_COL];

    inicializar_lista(alumnos);
    menu(alumnos);

    return 0;
}

void menu(alumno_t alumnos[][MAX_COL]){
    int op=0;
    int input_usuario=0;

    do{
        printf("\n\n||| MENU DE NAVEGACION |||\n");
        printf("\nSeleccione una opcion:");
        printf("\n[1] Mostrar lista.");
        printf("\n[2] Registrar alumno nuevo.");
        printf("\n[3] Borrar alumno.");
        printf("\n[4] Ordenar lista.");
        printf("\n[%d] Finalizar.",salida);
        printf("\nOpcion: ");
        scanf("%d",&op);

        switch (op){
        case opcion1:
            mostrar_lista(alumnos);
            break;
        case opcion2:
            do{
                registrar_alumno(alumnos);

                printf("\nDesea Guardar otro item?\nSI-1 NO-0: ");
                scanf("%d",&input_usuario);
                if(input_usuario!=0 && input_usuario!=1){
                    valor_incorrecto();
                }
            }while(input_usuario!=0);
            break;
        case opcion3:
            break;
        case opcion4:
            ordenar_por_edad(alumnos);
            break;
        case salida:
            despedida();
            break;
        default:
            valor_incorrecto();
            break;
        }
    }while(op!=salida);
}

void inicializar_lista(alumno_t alumnos[][MAX_COL]){

    for(int i=0;i<MAX_ROW;i++){
        for(int j=0;j<MAX_COL;j++){
            alumnos[i][j].codigo=0;
            alumnos[i][j].edad=0;
            strcpy(alumnos[i][j].nombre,"N/A");
            alumnos[i][j].promedio=0;
        }
    }

}

void registrar_alumno(alumno_t alumnos[][MAX_COL]){
    int codigo=0;
    int edad=0;
    int fila=0;
    int col=0;
    float promedio=0;
    bool cod_ok=false;
    bool ubicacion_ok=false;

    printf("\n|++| NUEVO ALUMNO |++|\n");

    do{
        printf("\nIngrese un codigo de %d digitos.",sizeof(max_cod));
        printf("\nCodigo: ");
        scanf("%d",&codigo);

        if(codigo>max_cod || codigo<min_cod){
            printf("\nERROR. El codigo no puede ser menor a %d ni mayor a %d.",min_cod,max_cod);
            printf("\nIngreselo nuevamente.\n");
        }else if(validar_codigo(alumnos,codigo)){
            printf("\nERROR. El codigo ya existe.");
            printf("\nIngreselo nuevamente.\n");
        }else{
            cod_ok=true;
        }

    }while(!cod_ok);

    do{
        printf("\nIngrese la ubicacion en el salon.");
        printf("\nFila (%d a %d): ",MIN_ROW,MAX_ROW);
        scanf("%d",&fila);
        printf("Asiento (%d a %d): ",MIN_COL,MAX_COL);
        scanf("%d",&col);

        if(fila>MAX_ROW || fila<MIN_ROW || col>MAX_COL || col<MIN_COL){
            valor_incorrecto();
        }else if(validar_lugar(alumnos,fila-1,col-1)){
            printf("\nYa existe un registro en ese lugar. Ingrese otro.\n");
        }else{
            ubicacion_ok=true;
            fila-=1;
            col-=1;
        }
    }while(!ubicacion_ok);

    printf("\nIngrese el Nombre: \n");
    fflush(stdin);
    fgets(alumnos[fila][col].nombre,sizeof(alumnos[fila][col].nombre),stdin);
    alumnos[fila][col].nombre[strcspn(alumnos[fila][col].nombre,"\n")]='\0';

    do{
        printf("\nIngrese la edad del alumno.\nEdad: ");
        scanf("%d",&edad);

        if(edad>max_edad || edad<min_edad){
            printf("\nERROR. La edad no puede ser menor que %d ni mayor que %d.\n",min_edad,max_edad);
        }
    }while(edad>max_edad || edad<min_edad);

    do{
        printf("\nIngrese el promedio del alumno.\nPromedio: ");
        scanf("%f",&promedio);

        if(promedio>max_nota || promedio<min_nota){
            printf("\nERROR. El promedio no puede ser menor que %d ni mayor que %d.\n",min_nota,max_nota);
        }
    }while(promedio>max_nota || promedio<min_nota);

    alumnos[fila][col].codigo=codigo;
    alumnos[fila][col].edad=edad;
    alumnos[fila][col].promedio=promedio;

    printf("\nDATOS INGRESADOS");
    printf("\n| ROW | COL | CODIGO | EDAD | PROM. | NOMBRE");
    printf("\n|  %d  |  %d  |  %04d  | %4d | %04.1f  | %s\n",fila+1,col+1,alumnos[fila][col].codigo,alumnos[fila][col].edad,alumnos[fila][col].promedio,alumnos[fila][col].nombre);

}

void mostrar_lista(alumno_t alumnos[][MAX_COL]){

    printf("\n***LISTA DE ALUMNOS***\n");
    printf("Referencia: ROW->Fila COL->Asiento\n");
    printf("\n\n| ROW | COL | CODIGO | EDAD | PROM. | NOMBRE\n");
    printf("-----------------------------------------------");
    for(int i=0;i<MAX_ROW;i++){
        for(int j=0;j<MAX_COL;j++){
            printf("\n|  %d  |  %d  |  %04d  | %4d | %04.1f  | %s",i+1,j+1,alumnos[i][j].codigo,alumnos[i][j].edad,alumnos[i][j].promedio,alumnos[i][j].nombre);
        }
        printf("\n-----------------------------------------------");
    }
    
}

bool validar_codigo(alumno_t alumnos[][MAX_COL],int codigo){
    for(int i=0;i<MAX_ROW;i++){
        for(int j=0;j<MAX_COL;j++){
            if(alumnos[i][j].codigo==codigo){
                return true;
            }
        }
    }
    return false;
}

bool validar_lugar(alumno_t alumnos[][MAX_COL],int fila,int col){
    if(alumnos[fila][col].codigo!=0){
        return true;
    }else{
        return false;
    }
}

void ordenar_por_edad(alumno_t alumnos[][MAX_COL]){
    alumno_t aux;
    alumno_t aux_array[MAX_ROW*MAX_COL];
    int index=0;

    for(int i=0;i<MAX_ROW;i++){
        for(int j=0;j<MAX_COL;j++){
            aux_array[index++]=alumnos[i][j];
        }
    }

    index=0;

    for(int i=0;i<(MAX_ROW*MAX_COL);i++){
        for(int j=0;j<(MAX_ROW*MAX_COL)-i-1;j++){
            if(aux_array[j].edad<aux_array[j+1].edad){
                aux=aux_array[j+1];
                aux_array[j+1]=aux_array[j];
                aux_array[j]=aux;
            }
        }
    }

    for(int i=0;i<MAX_ROW;i++){
        for(int j=0;j<MAX_COL;j++){
            alumnos[i][j]=aux_array[index++];
        }
    }

    printf("\nSe ordeno la lista correctamente. Lista actualizada:\n");

    mostrar_lista(alumnos);

}