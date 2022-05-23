#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    char nome [ 10 ];
    setlocale ( LC_ALL, "" );

    /*
        O código a seguir utiliza uma característica específica da linguagem C:
        tratar um caractere tanto pelo seu sí­mbolo, quanto por seu valor na tabela ASCII.
        
        Neste caso, utilizando o valor da tabela ASCII, tem-se a seguinte situação:
        para converter uma letra para maiúscula, basta subtrair o valor 32 de seu código
        na tabela ASCII.

        Exemplos:
            'a' minúsculo - código ASCII 97
            'A' maiúsculo - código ASCII 65
            'b' minúsculo - código ASCII 98
            'B' maiúsculo - código ASCII 66
            ...
            'z' minúsculo - código ASCII 122
            'Z' maiúsculo - código ASCII  90
    */

    strcpy ( nome, "jose" );
    printf ( "Nome: %s.\n", nome );
    printf ( "%i\n", nome[0] );
    nome [ 0 ] -= 32;
    printf ( "Nome com inicial maiúscula: %s.\n", nome );
    return 0;
}