#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAM_MAX_NOME 200
#define TAM_MAX_VET    5

typedef struct DemoStruct
{
    char nome [ TAM_MAX_NOME ];
    int diaContratacao;
    int mesContratacao;
    int anoContratacao;
    float salario;
} tipoRegistro;


int main ( int argc, char *argv[] )
{
    tipoRegistro vetFuncionarios [ TAM_MAX_VET ];
    
    setlocale (LC_ALL, "" );

    printf ( "Programa - Demonstração de Registros (struct) em C.\n" );

    printf ( "Realizando a entrada de dados...\n" );
    for ( int i = 0; i <TAM_MAX_VET; i++ )
    {
        printf ( "Digite o nome: " );
        fflush ( stdin );
        //fgets ( vetFuncionarios[i].nome, TAM_MAX_VET - 1; stdin );
        scanf  ( "%[^\n]s", vetFuncionarios[i].nome );

        printf ( "Digite o dia (DD), mês (MM) e ano (AAAA) da contratação: " );
        scanf  ( "%i%i%i",
            &vetFuncionarios[i].diaContratacao,
            &vetFuncionarios[i].mesContratacao,
            &vetFuncionarios[i].anoContratacao );

        printf ( "Digite o salário inicial: R$ " );
        scanf  ( "%f", &vetFuncionarios[i].salario );
    }

    printf ( "\n\nExibindo os dados informados...\n" );
    for ( int i = 0; i < TAM_MAX_VET; i++ )
    {
        printf ( "Nome do funcionário: %s.\n", vetFuncionarios[i].nome );
        printf ( "Data de contratação: %02i/%02i/%04i.\n",
            vetFuncionarios[i].diaContratacao,
            vetFuncionarios[i].mesContratacao,
            vetFuncionarios[i].anoContratacao );
        printf ( "Salário inicial....: R$ %.2f.\n\n", vetFuncionarios[i].salario );
    }

    return 0;
}