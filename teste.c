#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int cep = 12345678;
    float aux;



    printf("%i", (int)cep/100);
    printf("-\n");
    aux = (float)cep/1000 - cep/1000;
    printf("%f",aux*1000);




    return 0;
}
