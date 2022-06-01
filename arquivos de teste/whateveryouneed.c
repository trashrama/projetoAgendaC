#include <stdio.h>

#ifndef MAX
#define MAX 10
#endif

int main(int argc, char const *argv[]){
    printf("\n============================================== DADOS ===============================================\n\n");
    char* colunas[] = {"NOME", "ENDEREÇO", "CEP", "TELEFONE", "TIPO DE CONTATO", "EMAIL", "REDE SOCIAL", "NOTA"};
    printf("%*s | %*s | %*s | %*s | %*s | %*s | %*s | %*s\n", -13, colunas[0], -MAX, colunas[1], -MAX, colunas[2], -MAX, colunas[3], -MAX, colunas[4], -MAX, colunas[5], -MAX, colunas[6], -MAX, colunas[7]);


    printf("%-3s", agenda.contato[c].nome);

    

    return 0;
}
