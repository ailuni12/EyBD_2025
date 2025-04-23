#include <stdio.h>

int main(){
    int i,j,k=1;
    printf("ingrese a: ");
    scanf("%d",&i);

    for(j=i;j>1;j--){
        k=k*j;
        printf("i:%d|j:%d|k:%d\n",i,j,k);
    }

    printf("num: %d factorial: %d",i,k);

    return 0;
}