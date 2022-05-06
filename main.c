#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAMVET 3

struct st_pessoa{
    char nome[50], cidade[20], endereco[100], estado[20], email[100], nota[200];
    int telefone, cep, ehFixo;
};


int main(int argc, char const *argv[]){
    struct st_pessoa pessoas[TAMVET];

    char opcao[2];
    int parar = FALSE;
    int i = 0;

    while (parar != TRUE){
        
        printf("Digite seu nome: \n");
        fgets(pessoas[i].nome, 50, stdin);

        printf("Digite sua cidade: \n");
        fgets(pessoas[i].cidade, 20, stdin);

        printf("Digite seu CEP: \n");
        scanf("%i", &pessoas[i].cep);
        getchar();

        printf("Digite seu estado: \n");
        fgets(pessoas[i].estado, 50, stdin);

        printf("Digite seu endereço: \n");
        fgets(pessoas[i].endereco, 50, stdin);

        printf("Digite seu telefone: \n");
        scanf("%i", &pessoas[i].telefone);
        getchar();

        printf("O telefone é fixo? (S/N): \n");
        scanf("%c", &opcao);

        if (toupper(opcao[0]) == 'S'){
            pessoas[i].ehFixo = TRUE;
        }else{
            pessoas[i].ehFixo = FALSE;
        }
        getchar();

        printf("Digite seu e-mail: \n");
        fgets(pessoas[i].email, 100, stdin);
        
        printf("Deseja digitar uma nota? (S/N): \n");
        scanf("%c", &opcao);
        if (toupper(opcao[0]) == 'S'){
            printf("Digite uma nota: \n");
            fgets(pessoas[i].nota, 200, stdin);    
        }
        getchar();


        printf("Deseja adicionar mais alguém? (S/N): \n");
        scanf("%c", &opcao);
        if (toupper(opcao[0]) == 'N'){
            parar = TRUE;
        }
        getchar();
        i++;
    }

    for (int c = 0; c < i; c++){
        printf("\n=========== DADOS ===========\n");
        printf("Nome: %s", pessoas[c].nome);
        printf("Cidade: %s", pessoas[c].cidade);
        printf("CEP: %i\n", pessoas[c].cep);
        printf("Estado: %s", pessoas[c].estado);
        printf("Endereço: %s", pessoas[c].endereco);
        printf("Telefone: %i\n", pessoas[c].telefone);
        printf("FIXO: ");
        if(pessoas[i].ehFixo == TRUE){
            printf("SIM");
        }else{
            printf("NÃO");
        }
        printf("\nE-mail: %s\n", pessoas[i].email);
        printf("Nota: %s", pessoas[i].nota);
    }
    
    return 0;
}


