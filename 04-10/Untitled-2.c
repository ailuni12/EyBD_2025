#include <stdio.h>

int main(void){
    int i, a;
    int *ptr;
    printf("Ingrese i:");
    scanf("%d",&i);
    
    ptr=&i;
    a=*ptr; //asigna la desreferencia de ptr

    printf("contenido de i: %d direccion de i: %p\n",i,&i);
    printf("contenido de a: %d direccion de a: %p\n",a,&a);
    printf("contenido de ptr: %d direccion de ptr: %p\n",*ptr,(void *)ptr);
    
    *ptr=9;

    printf("direccion de a: %p\n",(void *)&a);
    printf("valor de i: %d direccion de i: %p\n",i,(void *)&i);
    printf("direccion de ptr: %p\n",(void *)ptr);
    
    return 0;
}