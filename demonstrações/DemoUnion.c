#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAM_DIA_SEMANA 15

enum tipoEnumDias { DOM = 1, SEG, TER, QUA, QUI, SEX, SAB };

typedef struct DemoStruct
{
    char  campo_char;
    int   campo_int;
    float campo_float;
    enum tipoEnumDias diaDaSemana;
} tipoRegistro;

typedef union DemoUnion
{
    char campo_char;
    int  campo_int;
    float campo_float;
} tipoUnion;

void exibirDiaDaSemana ( tipoRegistro meuRegistro, char diaPorExtenso[] );

int main ( int argc, char *argv[] )
{
    char diaDaSemana [ TAM_DIA_SEMANA ];
    strcpy ( diaDaSemana, "" );

    setlocale (LC_ALL, "" );

    // Tratamento de struct
    struct DemoStruct meuRegistro;

    meuRegistro.campo_char = 'a';
    meuRegistro.campo_float = 0.0F;
    meuRegistro.campo_int = 0;
    meuRegistro.diaDaSemana = SAB;

    printf ( "Valor do campo da estrutura char: %c.\n", meuRegistro.campo_char );
    printf ( "Valor do campo da estrutura float: %f.\n", meuRegistro.campo_float );
    printf ( "Valor do campo da estrutura int: %i.\n", meuRegistro.campo_int );
    exibirDiaDaSemana ( meuRegistro, diaDaSemana );
    printf ( "Dia da semana por extenso: %s.\n", diaDaSemana );
    printf ( "Tamanho (em bytes) de tipoRegistro: %i.\n", sizeof ( tipoRegistro ) );

    // Tratamento de union
    union DemoUnion minhaUnion;

    minhaUnion.campo_float = 0.0F;
    minhaUnion.campo_int = 0;
    minhaUnion.campo_char = 'z';

    printf ( "\n\n" );
    printf ( "Valor do campo da union char: %c.\n", minhaUnion.campo_char );
    printf ( "Valor do campo da union float: %f.\n", minhaUnion.campo_float );
    printf ( "Valor do campo da union int: %i.\n", minhaUnion.campo_int );
    printf ( "Tamanho (em bytes) de tipoUnion: %i.\n", sizeof ( tipoUnion ) );

    return 0;
}

void exibirDiaDaSemana ( tipoRegistro meuRegistro, char diaPorExtenso[] )
{
    switch ( meuRegistro.diaDaSemana )
    {
        case DOM:
            //printf ( "Domingo.\n" );
            strcpy ( diaPorExtenso, "Domingo" );
            break;
        case SEG:
            //printf ( "Segunda-Feira.\n" );
            strcpy ( diaPorExtenso, "Segunda-Feira" );
            break;
        case TER:
            //printf ( "Terça-Feira.\n" );
            strcpy ( diaPorExtenso, "Terça-Feira" );
            break;
        case QUA:
            //printf ( "Quarta-Feira.\n" );
            strcpy ( diaPorExtenso, "Quarta-Feira" );
            break;
        case QUI:
            //printf ( "Quinta-Feira.\n" );
            strcpy ( diaPorExtenso, "Quinta-Feira" );
            break;
        case SEX:
            //printf ( "Sexta-Feira.\n" );
            strcpy ( diaPorExtenso, "Sexta-Feira" );
            break;
        case SAB:
            //printf ( "Sábado.\n" );
            strcpy ( diaPorExtenso, "Sábado" );
            break;
    }
}