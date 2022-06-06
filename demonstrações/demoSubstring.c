#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main ( int argc, char *argv[] )
{
    const char *myString = "Brasilia Mais Alguma Coisa";
    const char subStr[7];

    setlocale ( LC_ALL, "" );

    strncpy ( subStr, myString, 6 );
    printf ( "Subcadeia com os 6 primeiros caracteres: \"%s\".\n", subStr );
    return 0;
}