#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAMVET 10

// Protótipos de funções
void limparTela ( void );
void lerVetor ( int vetor[] );
void exibirVetor ( int vetor [] );
int somarElementos ( int vetor [] );
int realizarBuscaSequencial ( int chave, int vetor [] );
int realizarBuscaBinaria ( int chave, int vetor [] );
void ordenarVetor ( int vetor [] );
void aguardarParaSeguir ( void );

int main ( int argc, char *argv[] )
{
    int chave, opcao, pos, vetor [ TAMVET ];

    setlocale ( LC_ALL, "portuguese" );


    do
    {
        printf ( "Programa: Exercício de vetores e subrotinas...\n" );

        printf ( "****************************************************\n" );
        printf ( "* 1 - Ler elementos do vetor                       *\n" );
        printf ( "* 2 - Exibir elementos do vetor                    *\n" );
        printf ( "* 3 - Somar elementos do vetor                     *\n" );
        printf ( "* 4 - Fazer busca sequencial de uma chave no vetor *\n" );
        printf ( "* 5 - Fazer busca binária de uma chave no vetor    *\n" );
        printf ( "* 6 - Ordenar elementos do vetor                   *\n" );
        printf ( "* 0 - Finalizar                                    *\n" );
        printf ( "****************************************************\n" );
        printf ( "Digite sua opção: " );
        scanf  ( "%i", &opcao );

        switch ( opcao )
        {
        case 0:
            printf ( "Finalizando aplicação!\n" );
            break;
        case 1:
            printf ( "Você selecionou a opção para ler os elementos do vetor!\n" );
            lerVetor ( vetor );
            break;
        case 2:
            printf ( "Exibindo os elementos do vetor!\n" );
            exibirVetor ( vetor );
            break;
        case 3:
            printf ( "A soma dos elementos do vetor é: %i.\n", somarElementos ( vetor ) );
            break;
        case 4:
            printf ( "Você selecionou a opção para fazer a busca sequencial de uma chave!\n" );

            printf ( "Informe a chave a ser buscada: " );
            scanf  ( "%i", &chave );

            pos = realizarBuscaSequencial ( chave, vetor );
            if ( pos < 0 )
            {
                printf ( "A chave %i não foi encontrada.\n", chave );
            }
            else
            {
                printf ( "A chave %i foi encontrada na posição: %i.\n",
                    chave, pos );
            }
            break;
        case 5:
            printf ( "Você selecionou a opção de busca binária!\n" );
            printf ( "Atenção: é necessário que o vetor esteja ordenado!\n" );

            ordenarVetor ( vetor );

            printf ( "Informe a chave a ser buscada: " );
            scanf  ( "%i", &chave );

            pos = realizarBuscaBinaria ( chave, vetor );
            if ( pos < 0 )
            {
                printf ( "A chave %i não foi encontrada.\n", chave );
            }
            else
            {
                printf ( "A chave %i foi encontrada na posição: %i.\n",
                    chave, pos );
            }
            break;
        case 6:
            printf ( "Você selecionou a opção de ordenação do vetor!\n" );
            ordenarVetor ( vetor );
            break;
        default:
            printf ( "Opção inválida!\n" );
        }

        aguardarParaSeguir ();
    }
    while ( opcao != 0 );
    return 0;
}

void limparTela ( void )
{
#ifdef __linux__
    system ( "clear" );
#elif _WIN32
    system ( "cls" );
#endif
}

void lerVetor ( int vetor[] )
{
    printf ( "Lendo os elementos do vetor:\n" );
    for ( int i = 0; i < TAMVET; i++ )
    {
        printf ( "Informe o %iº elemento do vetor: ", i + 1 );
        scanf  ( "%i", &vetor[ i ] );
    }

}

void exibirVetor ( int vetor [] )
{
    printf ( "Imprimindo os elementos do vetor:\n" );
    for ( int i = 0; i < TAMVET; i++ )
    {
        printf ( "Vet[%02i] = %i\n", i, vetor[ i ] );
    }
}

int somarElementos ( int vetor [] )
{
    int soma = 0;
    for ( int i = 0; i < TAMVET; i++ )
    {
        soma += vetor [ i ];
    }

    return soma;
}

int realizarBuscaSequencial ( int chave, int vetor [] )
{
    for ( int i = 0; i < TAMVET; i++ )
    {
        if ( chave == vetor [ i ] )
        {
            return i;
        }
    }

    // Este retorno significa que a chave não foi encontrada
    return -1;
}

void ordenarVetor ( int vetor [] )
{
    int aux;

    for ( int i = 0; i < TAMVET - 1; i++ )
    {
        for ( int j = i + 1; j < TAMVET; j++ )
        {
            if ( vetor [ i ] > vetor [ j ] )
            {
                aux = vetor [ i ];
                vetor [ i ] = vetor [ j ];
                vetor [ j ] = aux;
            }
        }
    }
}

int realizarBuscaBinaria ( int chave, int vetor [] )
{
    int ini = 0,
        fim = TAMVET - 1;
    int meio;

    while ( ini <= fim )
    {
        meio = ( ini + fim ) / 2;
        if ( chave == vetor [ meio ] ) // Achou!
        {
            return meio;
        }
        else
        {
            if ( chave < vetor [ meio ] )
            {
                fim = meio - 1;
            }
            else
            {
                ini = meio + 1;
            }
        }
    }

    return -1;
}

void aguardarParaSeguir ( void )
{
    printf ( "\n\nTecle ENTER para continuar..." );
    getchar ();
    getchar ();
    limparTela ();
}