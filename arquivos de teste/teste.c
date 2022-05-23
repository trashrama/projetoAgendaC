#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    char nome[30];
    nome[strcspn(nome, "\n")] = 0;

   

    printf("%s", nome);
    return 0;
}
