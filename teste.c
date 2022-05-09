#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int cep = 12345678;
  
    int aux = cep - ( (cep/10000000) * 10000000 );
    int aux2 = aux - (aux/1000000) * 1000000;
    int aux3 = aux2 - (aux2/100000) * 100000;
    int aux4 = aux3 - (aux3/10000) * 10000;
    int aux5 = aux4 - (aux4/1000) * 1000;



    printf("%i", (int)cep/1000);
    printf("-");
    printf("%i\n", aux5);

    return 0;
}
