
#ifndef UTILES_H_  // guardas de inclusión
#define UTILES_H_

#include <stdio.h>
#include <conio.h>

void tecla(void)
{
    printf("\nPresione cualquier tecla para continuar!!!");
    getch();
}
void linea(int x)
{

    int i;
    for (i = 1; i < x; i++)
        printf("*");
}
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void utf8()
{
    #ifdef _WIN32
      system("chcp 65001 < nul");
    #endif
}
#include <stdio.h>
#include <stdlib.h>

int leerEntero(const char *mensaje)
{
    char buffer[100];
    int numero;
    int flag = 1;

    while (flag)
    {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if (sscanf(buffer, "%d", &numero) == 1)
            {
                flag = 0;
            }
            else
            {
                printf("Entrada inválida. Intente nuevamente.\n");
            }
        }
    }
    return numero;
}

#endif /* UTILES_H_ */
