#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/*  Queremos criar uma ficha para agrupar os dados de um aluno
    1. Matrícula, (20212135009999)
    2. Nome completo,
    3. Diário,
    4. N1,
    5. N2,
    6. Frequência.
 */

#define TAM_MAX_MATR  15
#define TAM_MAX_NOME 200

// struct == Registro == Ficha
typedef struct StructAluno
{
    char matricula [ TAM_MAX_MATR ];
    char nomeCompleto [ TAM_MAX_NOME ];
    unsigned int diario;
    float N1;
    float N2;
    float freq;
    /* data */
} tipoRegAluno;

typedef union UnionAluno
{
    char matricula [ TAM_MAX_MATR ];
    char nomeCompleto [ TAM_MAX_NOME ];
    unsigned int diario;
    float N1;
    float N2;
    float freq;
    /* data */
} tipoUniAluno;

int main ( int argc, char *argv[] )
{
    char str1 [ TAM_MAX_MATR ],
         str2 [ TAM_MAX_MATR ];

    tipoRegAluno regAluno;
    int resultStrCmp;

    // regAluno.freq = freqAluno;
    // scanf ( "%f", &regAluno.freq );
    // printf ( "%.2f", regAluno.freq )

    printf ( "Digite o primeiro nome: " );
    fflush ( stdin );
    scanf  ( "%[^\n]s", str1 );

    printf ( "Digite o segundo nome: " );
    fflush ( stdin );
    scanf  ( "%[^\n]s", str2 );

    printf ( "Nome 1: %s.\n", str1 );
    printf ( "Nome 2: %s.\n", str2 );

    resultStrCmp = strcmp ( str1, str2 );
    if ( resultStrCmp < 0 )
    {
        printf ( "%s < %s.\n", str1, str2 );
    }
    else if ( resultStrCmp == 0 )
         {
             printf ( "%s == %s.\n", str1, str2 );
         }
         else
         {
             printf ( "%s > %s.\n", str1, str2 );
         }

    /*
    for ( int i = 0; i < TAM_VET - 1; i++ )
    {
        for ( int j = i + 1; j < TAM_VET; j++ )
        {
            resultStrCmp = strcmp ( contato[ i ].nome, contato[ j ].nome );
            if ( resultStrCmp > 0 )
            {
                // Fica como tarefa, certificar se é possível permutar
                // todos os campos de um registro por vez ou se há   a
                // necessidade de permutar cada campo individualmente.
                // Neste último caso, recomenda-se criar uma função pa
                // ra permutar os campos.

                aux = contato[i];
                contato[i] = contato[j];
                contato[j] = aux;
            }
        }
    }
    */

    return 0;
}