#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

enum tipoEndereco { ALAMEDA, AVENIDA, PRACA, RODOVIA, RUA, TRAVESSA };

char *obterNomeEndereco ( enum tipoEndereco tpEnd )
{
    const char *nomeEndereco[] =
    {
        "Al.", "Av.", "Pr.", "Rod.", "R.", "Tr."
    };

    return ( nomeEndereco [ tpEnd ] );
}

typedef struct
{
    char nome [ 100 ];
    char endereco [ 200 ];
    enum tipoEndereco tpEnd;
    int numero;
    char bairro [ 50 ];
    char email [ 60 ];
} tipoRegistro;

int main ( int argc, char *argv[] )
{
    tipoRegistro contatos [ 10 ];
    int nContatos;

    setlocale ( LC_ALL, "" );

    printf ( "Programa: Demonstração de impessão em tabela.\n" );

    printf ( "Digite o número de contatos a inserir: " );
    scanf  ( "%i", &nContatos );

    for ( int i = 0; i < nContatos; i++ )
    {
        printf ( "Digite o nome: " );
        fflush ( stdin );
        scanf  ( "%[^\n]s", contatos[i].nome );

        printf ( "Digite o tipo de endereço:\n" );
        printf ( "1 - Alameda\n2 - Avenida\n3 - Praça\n4 - Rodovia\n5 - Rua\n6 - Travessa.\n" );
        printf ( "Digite sua opção: " );
        fflush ( stdin );
        scanf  ( "%i", &contatos[i].tpEnd );

        printf ( "Digite o endereço: " );
        fflush ( stdin );
        scanf  ( "%[^\n]s", contatos[i].endereco );

        printf ( "Digite o número: " );
        fflush (stdin );
        scanf  ( "%i", &contatos[i].numero );

        printf ( "Digite o bairro: " );
        fflush ( stdin );
        scanf  ( "%[^\n]s", contatos[i].bairro );

        printf ( "Digite o e-mail: " );
        fflush ( stdin );
        scanf  ( "%[^\n]s", contatos[i].email );
    }

    char subStrNome [ 16 ];
    char subStrEnd  [ 21 ];
    char subStrBairro [ 11 ];
    for ( int i = 0; i < nContatos; i++ )
    {
        strncpy ( subStrNome , contatos[i].nome, 15 );
        // strncpy ( subStrEnd  , contatos[i].endereco, 20 );

        sprintf ( subStrEnd, "%s %s, %i",
            obterNomeEndereco ( contatos[i].tpEnd),
            contatos[i].endereco, contatos[i].numero );

        strncpy ( subStrBairro, contatos[i].bairro, 10 );
        printf ( "%-15s | %-20s | %-10s | %15s\n",
            subStrNome, subStrEnd,
            subStrBairro, contatos[i].email );
    }

    return 0;
}