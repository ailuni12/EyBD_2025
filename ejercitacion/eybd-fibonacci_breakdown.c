#include <stdio.h>

int fibonacci (int);

int main (void){
    int num = 0;

    printf("Ingrese un valor: ");
    scanf("%d",&num);
    
    for(int i=0;i<num;i++){
        printf("\nfor en main\n");
        printf("i:%d|i-1:%d|i-2:%d\n",i,i-1,i-2);
        printf("resultado: %d\n",fibonacci(i));
    }
}

int fibonacci (int num){
    printf("\nCalling function for '%d'\n",num);
    if(num==0 || num==1){
        return num;
    }else{
        int res = fibonacci(num-1)+fibonacci(num-2);
        printf("Returning %d for fibonacci(%d)\n",res,num);
        return res;
    }
}