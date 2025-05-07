#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define arrsize 9 //8 espacios para el numero binario + 1 para el \0 

int bintodec(char *, int);

int main(void){
    char binstring[arrsize];
    int length=0;
    int j=0;

    length=sizeof(binstring)/sizeof(binstring[0]);

    printf("Ingrese codigo en binario: ");
    fgets(binstring,length,stdin);
    binstring[strcspn(binstring,"\n")]=0;

    printf("\narr size: %d\n",length);
    //tamaño de la cadena dentro de main

    for(int i=0;i<length;i++){
        printf("\nInput: %c",binstring[i]);
    }

    printf("\n");

    for(int i=(length-2);i>=0;i--){
        printf("i: %d ",i);
        printf("c: %c\n",binstring[j]);
        j++; 
    }

    printf("\nDecimal: %d",bintodec(binstring,length));
    printf("\nCaracter ASCII: %c",bintodec(binstring,length));

    return 0;
}

int bintodec(char *numerobin, int length){
    int j=0, output=0;

    //binario a decimal

    for(int i=(length-2);i>=0;i--){
        if(numerobin[j]=='1'){
            output+=pow(2,i);
        }
        j++;
    }

    return output;
}