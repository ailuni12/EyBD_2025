#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int p(char *);
int bintodec(char *);

int main(void){
    char binstring[9];
    int j=0;

    printf("Ingrese codigo en binario: ");
    fgets(binstring,sizeof(binstring),stdin);

    printf("\narr size: %d\n",sizeof(binstring));
    //tamaño de la cadena dentro de main

    for(int i=0;i<sizeof(binstring);i++){
        printf("\nInput: %c",binstring[i]);
    }

    printf("\n");
    printf("\narr size in function: %d\n",p(binstring));
    //tamaño de la cadena al pasarsela a una funcion

    for(int i=(sizeof(binstring)-2);i>=0;i--){
        printf("i: %d ",i);
        printf("c: %c\n",binstring[j]);
        j++; 
    }

    printf("\nDecimal: %d",bintodec(binstring));
    printf("\nCaracter ASCII: %c",bintodec(binstring));

    return 0;
}

int p(char *string){
    return sizeof(string);
}

int bintodec(char *numerobin){
    int j=0, output=0;

    //binario a decimal

    for(int i=(sizeof(numerobin)-1);i>=0;i--){
        if(numerobin[j]=='1'){
            output+=pow(2,i);
        }
        j++;
    }

    return output;
}