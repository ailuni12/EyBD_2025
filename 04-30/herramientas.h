#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int bintodec(char *);

int bintodec(char *numerobin){
    int j=0, output=0;

    for(int i=(sizeof(numerobin)-1);i>=0;i--){
        if(numerobin[j]=='1'){
            output+=pow(2,i);
        }
        j++;
    }

    return output;
}