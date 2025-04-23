#include <stdio.h>

int main (void){
    int num = 0;
    int a = 0;
    int b = 1;
    int res = 0;

    printf("Ingrese un valor: ");
    scanf("%d",&num);

    for(int i=0;i<num;i++){
        printf("%d ",a);
        res = a + b;
        a = b;
        b = res;
    }

}