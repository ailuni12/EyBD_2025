#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define F_ERROR "ERROR, no se pudo abrir "

int main(void){
    char *fn="text.txt";
    printf("%s'%s'\n",F_ERROR,fn);
    return 0;
}

