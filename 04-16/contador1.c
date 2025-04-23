#include <stdio.h>

int contador(int);

int main(void){
    int num = 0;
    
    printf("Ingrese valor: ");
    scanf("%d",&num);

    if(num<=9){
        printf("tiene %d digito.",contador(num));
    }else{
        printf("tiene %d digitos.",contador(num));
    }

    return 0;
}

int contador(int num){
    if(num<=9){
        return 1;
    }else{
        return 1 + contador(num/10);
    }
}