#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMMAX_CEP 10

void lerFormatStr(char var[], int tamanho){
    fgets(var, tamanho-1, stdin);
    var[strcspn(var, "\n")] = 0;

    while (strlen(var) > tamanho-1){
        printf("Tamanho excedido!\nDigite novamente: ");
        fgets(var, tamanho-1, stdin);
        var[strcspn(var, "\n")] = 0;
    }

    /* 
    A função acima realiza a leitura de uma string, e
    a remoção do '\n' ao final desta.
    */
}

void printarCep(char cep[]){

    char cepPp[6], cepSp[5];
    strncpy(cepPp, &cep[0],5);
    strncpy(cepSp, &cep[5],3);
    cepPp[5] = cepSp[3] = '\0';
    printf("%s-%s\n", cepPp, cepSp);

}
int main(int argc, char const *argv[])
{
    char cep[TAMMAX_CEP];
    fgets(cep, TAMMAX_CEP-1, stdin);
    cep[strcspn(cep, "\n")] = 0;
    formatarCep(cep);


    return 0;
}
