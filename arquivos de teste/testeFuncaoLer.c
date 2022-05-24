#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define TAMMAX_AGENDA 5
//TAMMAX_AGENDA é uma pseucostante para número máximo de contatos na agenda.
#define TAMMAX_NOME 50
#define TAMMAX_ESCOLHA 2
//TAMMAX_ESCOLHA é uma pseucostante para tamanhos char, para opções de sim ou não.
#define TAMMAX_TIPOEND 8
//TAMMAX_TIPOEND é uma pseucostante para o tipo de endereço.
#define TAMMAX_ENDERECO 50
#define TAMMAX_TEL 13
#define TAMMAX_TIPOCONT 14
#define TAMMAX_EMAIL 50
#define TAMMAX_SM 20
//TAMMAX_SM é uma pseucostante para o nome de usuário rede social *(SM - Social Media)*.
#define TAMMAX_TIPOSM 15
//TAMMAX_TIPOSM é uma pseucostante para o tipo de rede social *(SM - Social Media)*.


struct st_pessoa{
    char nome[TAMMAX_NOME];
};

struct st_agenda{
    struct st_pessoa contato[TAMMAX_AGENDA];
}agenda, aux;

lerFormatar(char var[], int tamanho){
    fgets(var, tamanho-1, stdin);
    var[strcspn(var, "\n")] = 0;
}

int main(int argc, char const *argv[]){
    int total = 0;
    lerFormatar(agenda.contato[total].nome, TAMMAX_NOME);

    

    return 0;
}
