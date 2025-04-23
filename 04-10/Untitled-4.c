#include <stdio.h>

int factorial(int);

int main(){
    int i;
    printf("ingrese a: ");
    scanf("%d",&i);

    printf("factorial: %d",factorial(i));

    return 0;
}

int factorial(int a){
    if(a == 1){
      return 1;
    }else{
      printf("%d\n",a);
      return a*factorial(a-1);
    }
}