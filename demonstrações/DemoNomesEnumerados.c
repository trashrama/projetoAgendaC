#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*
 Definição do enumerado Endereco (Endereço). A vantagem de utilizar o tipo
 enumerado é facilitar a checagem de tipos e valores, em tempo de compila-
 ção, e dar maior legibilidade ao código da aplicação.

 Ao invés de simplesmente utilizar constantes numéricas, o tipo  enumerado
 permite utilizar apelidos (ALAMEDA, AVENIDA, ...) para representar  valo-
 res específicos, quando este conjunto de valores é reduzido.

 Outros usos potenciais são para dias da semana  (DOMINGO,  SEGUNDA,  ...,
 SÁBADO) e meses do ano (JANEIRO, ..., DEZEMBRO).
 */
enum enEndereco { ALAMEDA, AVENIDA, PRACA, RODOVIA, RUA, TRAVESSA };

/*
 A função obterNomesEndereco converte o valor (numérico) de  um  parâmetro
 enumerado na constante string correspondente. Esta abordagem é mais inte-
 ressante que utilizar estruturas de seleção para testar o valor enumerado
 e associá-lo à string correspondente.

 Neste caso, utiiza-se uma característica da linguagem de programação para
 utilizar o valor enumarado como índice de uma estrutura bidimensional  do
 tipo char.
 
 Obs.: Na linguagem C, não há vetores multidimensionais, apenas vetores de
 vetores. No caso, utiliza-se um ponteiro para o vetor de  char que contém
 os nomes dos tipo enumerado Endereço.

 Importante destacar que os nomes são definidos em uma variável com  modi-
 ficador const para que a cadeia de caracteres não seja perdida,  uma  vez
 que é declarada como variável local de uma subrotina.
 */
char *obterNomeEndereco ( enum enEndereco tpEnd );

int main ( int argc, char *argv[] )
{
    setlocale ( LC_ALL, "" );
    enum enEndereco tpEnd;

    printf ( "%4s | %s\n", "Enum", "Valor" );
    /*
     No laço abaixo, utiliza-se uma variável enumerada para  iterar  sobre
     os valores que a mesma possui. O operador de incremento  é  utilizado
     considerando que o enumerado é, apenas, um sub-faixa de inteiros.
     */
    for ( tpEnd = ALAMEDA; tpEnd <= TRAVESSA; tpEnd++ )
    {
        printf ( "%4i | %s.\n", tpEnd, obterNomeEndereco ( tpEnd ) );
    }

    return 0;
}

char *obterNomeEndereco ( enum enEndereco tpEnd )
{
    const char *nomeEndereco[] =
    {
        "Alameda", "Avenida", "Praça", "Rodovia", "Rua", "Travessa"
    };

    return ( nomeEndereco [ tpEnd ] );
}