#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
        char nombre[25];
		int edad;
		}Registro;

void CargaRegistro (FILE *);
void MuestraRegistro (FILE *);
void ContarRegistros (FILE *);

int main(){
    Registro persona;
    FILE *archivo;
    system("cls");
    system("color 9f");
    archivo=fopen("C:\\Users\\jonat\\Downloads\\Estructuras y bases de datos\\Archivos de Texto y Binarios\\Ejemplo_03\\datos.dat","ab");
    if(archivo!=NULL){
        printf ("Carga de registros (Nombre y Edad) en un archivo binario\n\n");
        CargaRegistro (archivo);
        fclose(archivo);
    }
    else{
        printf("Error en la apertura del archivo");
    }
    printf ("\n");
    archivo=fopen("datos.dat","rb");
    if(archivo!=NULL){
    /* Se usa lectura adelantada, de otro modo
	el último dato sale repetido */
        printf ("Muestra de registros (Nombre y Edad) de un archivo binario\n\n");
        MuestraRegistro (archivo);
		fclose(archivo);
		printf ("\n");
    }
    else{
        printf("Error en la apertura del archivo");
    }
    system("pause");
    archivo=fopen("datos.dat","rb");
    if(archivo!=NULL){
        ContarRegistros (archivo);
    }
    else{printf("Error en la apertura del archivo\n");}
    system("pause");
    return 0;
}

void CargaRegistro (FILE *archivo){
    Registro persona;
    char tecla;
    if(archivo!=NULL){
        do{
            fflush(stdin); /* Se vacía el buffer de teclado */
			printf("\nIntroduzca el nombre de la persona: ");
			scanf("%s",persona.nombre);
			if(strlen(persona.nombre)>0){
                printf("Introduzca la edad: ");
				scanf("%d",&(persona.edad));
				fwrite(&persona,sizeof(persona),1,archivo);//parametros: Dir de la variable, tamaño del dato
				// (en este caso del STRUCT), el 1 es que voy a escribir un solo registro, en archivo
            printf ("\n");
            }
        printf ("Desea continuar (s/n): ");
        fflush (stdin);
        tecla = getchar ();
        }while (tecla == 's');
    }
}

void MuestraRegistro (FILE *archivo){
    Registro persona;
    int i;
    char tecla;
    fread(&persona,sizeof(Registro),1,archivo);
	while(!feof(archivo)){
        printf("Nombre: %s, Edad: %d\n",persona.nombre, persona.edad);
        fread(&persona,sizeof(Registro),1,archivo);
    }
}

void ContarRegistros (FILE *archivo){
    int cantReg;
    fseek(archivo,0,SEEK_END);
    cantReg=ftell(archivo)/sizeof(Registro);
	printf("\nCantidad de registros en el archivo = %d\n",cantReg);
    printf ("\n");
}
