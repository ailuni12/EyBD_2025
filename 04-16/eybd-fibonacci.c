#include <stdio.h>

int fibonacci (int);

int main (void){
    int num = 0;

    printf("Ingrese la cantidad de digitos de la secuencia Fibonacci que quiera visualizar: ");
    scanf("%d",&num);
    
    for(int i=0;i<num;i++){
        printf("%d, ",fibonacci(i));
    }
}

int fibonacci (int num){
    if(num==0 || num==1){
        return num;
    }else{
        return fibonacci(num-1)+fibonacci(num-2);
    }
}