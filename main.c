#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAMVET 100

struct st_pessoa{
    char nome[50], cidade[20], endereco[100], estado[20], cep[13], email[100], nota[200], telefone[16];
    int ehFixo;
};

struct st_agenda{
    struct st_pessoa contato[100];
}agenda, aux;


int lerContatos(int *i){

    char opcao[2];
    int parar = FALSE;

    while (parar != TRUE){
        printf("Digite seu nome: \n");
        fgets(agenda.contato[*i].nome, 49, stdin);

        printf("Digite sua cidade: \n");
        fgets(agenda.contato[*i].cidade, 19, stdin);

        printf("Digite seu CEP: \n");
        fgets(agenda.contato[*i].cep, 12, stdin);

        printf("Digite seu estado: \n");
        fgets(agenda.contato[*i].estado, 19, stdin);

        printf("Digite seu endereço: \n");
        fgets(agenda.contato[*i].endereco, 99, stdin);

        printf("Digite seu telefone, com DDD e com o 9 na frente: \n");
        fgets(agenda.contato[*i].telefone, 15, stdin);

        printf("O telefone é fixo? (S/N): \n");
        scanf("%c", &opcao);

        if (toupper(opcao[0]) == 'S'){
            agenda.contato[*i].ehFixo = TRUE;
        }else{
            agenda.contato[*i].ehFixo = FALSE;
        }
        getchar();


        printf("Digite seu e-mail: \n");
        fgets(agenda.contato[*i].email, 99, stdin);

        printf("Deseja adicionar uma nota? (S/N)\n");
        scanf("%c", &opcao);
        if (toupper(opcao[0]) == 'N'){
            strcpy(agenda.contato[*i].nota, " ");
        }else{
            printf("Digite uma nota: \n");
            fgets(agenda.contato[*i].nota, 199, stdin); 
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
    return *i;
}

void mostrarContatos(int *total){
    if (*total == 0){
        printf("Ainda não há contatos registrados!\n");
        sleep(1);
    }else{
        printf("\n=========== DADOS ===========\n");
        for (int c = 0; c < *total; c++){
            printf("=========== CONTATO %i ===========\n", (c+1));
            printf("Nome: %s", agenda.contato[c].nome);
            printf("Cidade: %s", agenda.contato[c].cidade);
            printf("CEP: ");
            formatarCep(c, agenda.contato[c].cep);
            printf("Estado: %s", agenda.contato[c].estado);
            printf("Endereço: %s", agenda.contato[c].endereco);
            printf("Telefone: %s", agenda.contato[c].telefone);
            formatarTel(c, agenda.contato[c].telefone);

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

}

int excluirContato(int *total){
    int pos;

    printf("Digite o número do contato que deseja excluir: \n");
    scanf("%i", &pos);
    pos = pos-1;

    for (int i = pos; i < *total; i++){
        printf("%i", i);
        agenda.contato[i] = agenda.contato[i+1];
    }

    return (*total)--;
}

void formatarCep(int c, char cep[]){
  
    char str1[7];
    char str2[10];
    for (int i = 0; i < 5; i++){
         str1[i] = cep[i];
    }
    str2[0] = cep[5];
    str2[1] = cep[6];
    str2[2] = cep[7];

    printf("%s-%s\n", str1, str2);

}

void formatarTel(int c, char telefone[]){
    char ddd[4];
    char telpp[8];
    char telsp[8];
    char pref[3];

    int aux;


    ddd[0] = telefone[0];
    ddd[1] = telefone[1];


    pref[0] = telefone[2];

    telpp[0] = telefone[3];
    telpp[1] = telefone[4];
    telpp[2] = telefone[5];
    telpp[3] = telefone[6];

    printf("(%s) %s\n ", ddd, pref);
    //printf("%s-%s", telpp, telsp);

    

    //printf("%s", pref);

    
}


int main(int argc, char const *argv[]){
    int total = 0, opcao = 0;

    while(opcao != 4){
        printf("*********** AGENDA ***********\n");
        printf("1. Ver Agenda\n");
        printf("2. Adicionar Contatos\n");
        printf("3. Excluir Contatos\n");
        printf("4. Sair\n");
        printf("\nEscolha a opção: ");
        scanf("%i", &opcao);
        getchar();

        system("clear");

        switch (opcao){
        case 1:
            mostrarContatos(&total);
            break;
        case 2:
            lerContatos(&total);
            system("clear");
            break;
        case 3:
            excluirContato(&total);
            system("clear");
            break;
        case 4:
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


