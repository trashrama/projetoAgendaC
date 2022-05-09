#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAMVET 100

struct st_pessoa{
    char nome[50], cidade[20], endereco[100], estado[20], email[100], nota[200], telefone[12];
    int cep, ehFixo;
};

struct st_agenda{
    struct st_pessoa contato[100];
}agenda, aux;


int lerContatos(int *i){

    char opcao[2];
    int parar = FALSE;

    while (parar != TRUE){
        printf("Digite seu nome: \n");
        fgets(agenda.contato[*i].nome, 50, stdin);

        printf("Digite sua cidade: \n");
        fgets(agenda.contato[*i].cidade, 20, stdin);

        printf("Digite seu CEP: \n");
        scanf("%i", &agenda.contato[*i].cep);
        getchar();
        //fgets(agenda.contato[*i].cep, 12, stdin);

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
            printf("CEP: %i\n", agenda.contato[c].cep);
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

}

void printarCep(int total){
    aux = 0;
    agenda.contato[total].cep;
    printf("%i");
    //inutilizada, desenvolvendo a lógica no teste c
}

void organizarContatos(int *i){
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

// void formatarCep(int *total){

//     for (int i = 0; i < 9; i++){
//         aux.contato[*total-1].cep[i] = agenda.contato[*total-1].cep[i];
//     }
    
//     agenda.contato[*total-1].cep[5] = '-';

//     agenda.contato[*total-1].cep[6] = aux.contato[*total-1].cep[5];
//     //agenda.contato[*total-1].cep[7] = aux.contato[*total-1].cep[6];
//     //agenda.contato[*total-1].cep[8] = aux.contato[*total-1].cep[7];
//     //agenda.contato[*total-1].cep[9] = aux.contato[*total-1].cep[8];


//     for (int i = 5; i < 10; i--){
//         agenda.contato[*total-1].cep[i+1] = aux.contato[*total-1].cep[i];
//     }
    
// }

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
           // formatarCep(&total);
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


