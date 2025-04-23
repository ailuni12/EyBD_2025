#include <stdio.h>

int suma(int, int, int *);

int main(){
    int i, j ,k;
    printf("ingrese a: ");
    scanf("%d",&i);
    printf("ingrese b: ");
    scanf("%d",&j);

    suma(i,j,&k);

    printf("resultado: %d",k);

    return 0;
}

int suma(int a, int b, int *resultado){
    if(b==0){
        *resultado=a;
    }else{
        printf("a:%d | b:%d | res:%d\n",a,b,*resultado);
        suma(a,b-1,resultado);
        *resultado=*resultado+1;
        printf("res:%d\n",*resultado);
    }
}