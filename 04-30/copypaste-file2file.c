#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escribir(FILE *);
void copiar(FILE *, FILE *);

int main(void){
FILE *original, *copia;

original = fopen("original.txt", "w+");
if (!original) {
perror("Error opening original.txt");
exit(EXIT_FAILURE);
}

copia = fopen("copia.txt", "a+");
if (!copia) {
perror("Error opening copia.txt");
fclose(original);
exit(EXIT_FAILURE);
}

escribir(original);
rewind(original); // Reset file pointer to start
copiar(original, copia);

fclose(original);
fclose(copia);

return 0;
}

void escribir(FILE *orig){
char s[81];

printf("\nIngrese caracteres hasta [Ctrl+Z o Ctrl+D]:\n");

while (fgets(s, sizeof(s), stdin)) {
fputs(s, orig);
}

printf("\nSe guardó correctamente.\n");
}

void copiar(FILE *orig, FILE *copy){
char cad[81];

printf("\nCOPIANDO...\n");
while (fgets(cad, sizeof(cad), orig)) {
fputs(cad, copy);
}
printf("Se copió correctamente.\n");
}