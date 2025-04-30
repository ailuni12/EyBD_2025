#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

int contar(char *); //contador de palabras ejemplo

int contar(char *x){
    int contapal = 0, i = 0;

    if (x[i]!='\n'){

        while (x[i]!='\n'){

            while((x[i]!='\n')&&(x[i]==' ')){
                i++;
            }
            if(x[i]!='\n'){
                contapal++;
            }
            while((x[i]!=' ')&&(x[i]!='\n')){
                i++;
            }
        }

    }

    return (contapal);
}
