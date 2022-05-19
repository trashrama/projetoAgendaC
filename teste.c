#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char cep[13];
    fgets(cep, 12, stdin);

    char str1[6];
    char str2[5];
    for (int i = 0; i < 5; i++){
         str1[i] = cep[i];
    }

    printf("%s-", str1);


    str2[0] = cep[5];
    str2[1] = cep[6];
    str2[2] = cep[7];


    printf("%s\n", str2);

    return 0;
}
