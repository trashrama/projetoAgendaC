#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAM_DIA_SEMANA 15

enum tipoEnumDias { DOM = 1, SEG, TER, QUA, QUI, SEX, SAB };

int main ( int argc, char *argv[] )
{
    setlocale ( LC_ALL, "" );
    for ( int dia = DOM; dia <= SAB; dia++ )
    {
        switch ( dia )
        {
            case DOM:
                printf ( "Domingo\n" );
                break;
            case SEG:
                printf ( "Segunda\n" );
                break;
            case TER:
                printf ( "Terça\n" );
                break;
            case QUA:
                printf ( "Quarta\n" );
                break;
            case QUI:
                printf ( "Quinta\n" );
                break;
            case SEX:
                printf ( "Sexta\n" );
                break;
            case SAB:
                printf ( "Sábado\n" );
                break;
        }
    }

    return 0;
}