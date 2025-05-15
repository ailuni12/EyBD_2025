#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

bool existeNewline(char *);

int main(void){
    char string[10];
    int i=0;

    fgets(string,10,stdin);

    printf("%s",string);

    while(string[i]!='\0'){
        printf("[%c]",string[i]);
        i++;
    }

    printf("Existe newline?: %d",existeNewline(string));
}

bool existeNewline(char *string){
    int i=0;
    while(string[i]!='\0'){
        if((string[i]=='\n')){
            return 1;
        }
        i++;
    }
    return 0;
}