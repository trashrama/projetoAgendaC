#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAMVET 100

struct st_pessoa{
    char nome[50], cidade[20], endereco[100], estado[20], email[100], nota[200], cep[12], telefone[12];
    int ehFixo;
};

struct st_agenda{
    struct st_pessoa contato[100];
}agenda;


lerContatos(int *i){

    char opcao[2];
    int parar = FALSE;

    while (parar != TRUE){
        
        printf("Digite seu nome: \n");
        fgets(agenda.contato[*i].nome, 50, stdin);

        printf("Digite sua cidade: \n");
        fgets(agenda.contato[*i].cidade, 20, stdin);

        printf("Digite seu CEP: \n");
        fgets(agenda.contato[*i].cep, 12, stdin);

        printf("Digite seu estado: \n");
        fgets(agenda.contato[*i].estado, 50, stdin);

        printf("Digite seu endereço: \n");
        fgets(agenda.contato[*i].endereco, 50, stdin);

        printf("Digite seu telefone: \n");
        fgets(agenda.contato[*i].telefone, 12, stdin);

        printf("O telefone é fixo? (S/N): \n");
        scanf("%c", &opcao);

        if (toupper(opcao[0]) == 'S'){
            agenda.contato[*i].ehFixo = TRUE;
        }else{
            agenda.contato[*i].ehFixo = FALSE;
        }
        getchar();

        printf("Digite seu e-mail: \n");
        fgets(agenda.contato[*i].email, 100, stdin);

        printf("Deseja adicionar uma nota? (S/N)\n");
        scanf("%c", &opcao);
        if (toupper(opcao[0]) == 'N'){
            strcpy(agenda.contato[*i].nota, " ");
        }else{
            printf("Digite uma nota: \n");
            fgets(agenda.contato[*i].nota, 200, stdin); 
        }
        getchar();

        printf("Deseja adicionar mais alguém? (S/N): \n");
        scanf("%c", &opcao);
        if (toupper(opcao[0]) == 'N'){
            parar = TRUE;
        }
        getchar();
        (*i)++;
    }

}

mostrarContatos(int *i){
    printf("\n=========== DADOS ===========\n");
    for (int c = 0; c < *i; c++){
        printf("=========== CONTATO %i ===========\n", (c+1));
        printf("Nome: %s", agenda.contato[c].nome);
        printf("Cidade: %s", agenda.contato[c].cidade);
        printf("CEP: %s", agenda.contato[c].cep);
        printf("Estado: %s", agenda.contato[c].estado);
        printf("Endereço: %s", agenda.contato[c].endereco);
        printf("Telefone: %s", agenda.contato[c].telefone);
        printf("FIXO: ");
        if(agenda.contato[c].ehFixo == TRUE){
            printf("SIM");
        }else{
            printf("NÃO");
        }
        printf("\nE-mail: %s", agenda.contato[c].email);
        printf("Nota: %s", agenda.contato[c].nota);
        printf("\n\n");
    }

}

organizarContatos(int *i){
    char aux;
    for (int p = 0; p <= i-2; p++){
        for (int j = i+1; j <= i-1; j++){
            if (strcmp(agenda.contato[p].nome, agenda.contato[j].nome) > 0){
            strcpy(agenda.contato[p].nome, aux);
            strcpy(agenda.contato[p].nome, agenda.contato[j].nome);
            strcpy(agenda.contato[p].nome, aux);
            }
        }
    }
}

int main(int argc, char const *argv[]){
    int total = 0, opcao = 0;

    while(opcao != 3){
        printf("*********** AGENDA ***********\n");
        printf("1. Ver Agenda\n");
        printf("2. Adicionar Contatos\n");
        printf("3. Sair\n");
        printf("\nEscolha a opção: ");
        scanf("%i", &opcao);

        switch (opcao){
        case 1:
            mostrarContatos(&total);
            break;
        case 2:
            lerContatos(&total);
            break;
        case 3:
            printf("Saindo do Programa...\n");
            break;
        
        default:
            printf("Opção inválida!\n");
            getchar();
            break;
        }
    }
    //organizarContatos(&total);

    return 0;
}


