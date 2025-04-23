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
    printf("contador(%d) called\n", num);
    if(num<=9){
        printf("Returning 1 for %d\n", num);
        return 1;
    }else{
        int result = 1 + contador(num/10);
        printf("Returning %d for %d\n", result, num);
        return result;
    }
}