#include <stdio.h>

int sumanaturales (int);

int main (void){
    int num = 0;

    printf("Ingrese un valor: ");
    scanf("%d",&num);
    
    printf("resultado: %d\n",sumanaturales(num));
}

int sumanaturales (int num){
    if(num==0 || num==1){
        return num;
    }else{
        return num + sumanaturales(num-1);
    }
}