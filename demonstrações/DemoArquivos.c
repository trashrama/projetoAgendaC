#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define TAM_MAX_NOME 200

typedef struct DemoArquivos
{
    char nome[ TAM_MAX_NOME ];
    int diaContratacao;
    int mesContratacao;
    int anoContratacao;
    float salario;
} tipoRegistro;


int main ( int argc, char *argv[] )
{
    setlocale ( LC_ALL, "" );
    char cont;

    // printf ( "<mensagem>" );
    // Enviar uma mensagem para o dispositivo de saída padrão: stdout
    
    // scanf  ( "", &<variável> );
    // Fazer uma varredura no dispositivo de entrada padrão

    // stdprn: Impressora padrão
    // stderr: Dispositivo padrão para mensagens de erro
    // filePrt: Ponteiros para arquivos (conforme o uso)

    // Manipulação de arquivos em disco
    // 0. Declaração de um ponteiro para o arqivo,
    // 1. Abertura / criação do arquivo,
    // 2. Verificação se a abertura do arquivo foi bem sucedida,
    // 3. Leitura / escrita,
    // 4. Fechamento do arquivo.

    // Modo de processamento dos arquivos: binária ou ASCII.

    tipoRegistro meuRegistro;

    // Passo a passo:
    // 0. Declaração do ponteiro para o arquivo.
    FILE *ptrArquivo = NULL;

    // 1. Abertura / criação do arquivo
    ptrArquivo = fopen ( "dados.dat", "w" );

    // 2. Verificação se a abertura do arquivo foi bem sucedida
    if ( ptrArquivo == NULL )
    {
        printf ( "Erro ao abrir o arquivo. Finalizando programa...\n" );
        exit ( 0 );
    }

    do
    {
        /* code */
        printf ( "Digite o nome: " );
        fflush ( stdin );
        scanf  ( "%[^\n]s", meuRegistro.nome );

        printf ( "Digite o dia, mês e ano da contratação: " );
        scanf  ( "%i%i%i", &meuRegistro.diaContratacao,
            &meuRegistro.mesContratacao, &meuRegistro.anoContratacao );

        printf ( "Digite o salário: R$ " );
        scanf  ( "%f", &meuRegistro.salario );

        // 3. Leitura / escrita
        fprintf ( ptrArquivo, "%s;%i;%i;%i;%.2f\n",
            meuRegistro.nome,
            meuRegistro.diaContratacao,
            meuRegistro.mesContratacao,
            meuRegistro.anoContratacao,
            meuRegistro.salario );

        printf ( "Deseja continuar (S/N) ? " );
        fflush ( stdin );
        cont = tolower ( getchar () );

        system ( "cls" );
    }
    while ( cont == 's' );


    // 4. Fechamento do arquivo
    fclose ( ptrArquivo );
    ptrArquivo = NULL;

    return 0;
}