#include <stdio.h>

int fibonacci (int);

int main (void){
    int num = 0;

    printf("Ingrese un valor: ");
    scanf("%d",&num);
    
    for(int i=0;i<num;i++){
        printf("i:%d|i-1:%d|i-2:%d\n",i,i-1,i-2);
        printf("resultado: %d\n",fibonacci(i));
    }
}

int fibonacci (int num){
    if(num==0 || num==1){
        return num;
    }else{
        return fibonacci(num-1)+fibonacci(num-2);
    }
}