#include <stdio.h>

int main(void){
    int num=0;
    int *ptr;

    num=sizeof(num);
    printf("%d\n",num);
    num=sizeof(ptr);
    printf("%d\n",num);

}