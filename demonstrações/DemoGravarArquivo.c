#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAM_MAX_NOME_ARQUIVO 100
#define TAM_MAX_DADOS        200

int main ( int argc, char *argv[] )
{
    setlocale ( LC_ALL, "" );

    printf ( "Programa para ilustrar como gravar linhas em um arquivo de texto ASCII...\n" );
    printf ( "Você deve digitar mensagens que serão automaticamente gravadas no arquivo.\n" );
    printf ( "Para finalizar, basta teclar <ENTER> sem digitar texto algum em qualquer uma das linhas.\n" );

    char nomeArquivo [ TAM_MAX_NOME_ARQUIVO ];
    printf ( "\nNo entanto, antes de iniciar, por favor indique o nome do arquivo a ser criado: " );
    fflush ( stdin );
    scanf  ( "%[^\n]s", nomeArquivo );

    FILE *ptrArquivo = NULL;
    printf ( "\nAgora, vamos tentar criar o arquivos em disco...\n" );
    ptrArquivo = fopen ( nomeArquivo, "w" );

    if ( ptrArquivo == NULL )
    {
        printf ( "Não foi possível criar o arquivo.\n" );
        printf ( "Finaliando execução...\n" );
        exit ( 0 );
    }

    printf ( "Arquivo criado com sucesso...\n" );
    
    printf ( "\nAgora, vamos inserir conteúdo no arquivo...\n" );
    printf ( "Digite mensagens seguidas de <ENTER> ou, para finalizar, apenas o <ENTER>...\n" );

    char dados [ TAM_MAX_DADOS ];
    int  contMsg = 1;
    int  tamMsg = 0;
    do
    {
        strcpy ( dados, "" );
        printf ( "Msg. %02i: ", contMsg++ );
        fflush ( stdin );
        scanf  ( "%[^\n]s", dados );

        tamMsg = strlen ( dados );
        if ( tamMsg > 0 )
        {
            fprintf ( ptrArquivo, "%s\n", dados );
        }
    } while ( tamMsg > 0 );

    printf ( "\nVocê teclou <ENTER> com mensagem vazia, finalizando...\n" );
    printf ( "Fechando o arquivo: %s.\n", nomeArquivo );

    fclose ( ptrArquivo );
    ptrArquivo = NULL;

    return 0;
}