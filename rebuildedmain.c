#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define TAMMAX_AGENDA 100
//TAMMAX_AGENDA é uma pseucostante para número máximo de contatos na agenda.
#define TAMMAX_NOME 50
#define TAMMAX_ESCOLHA 2
//TAMMAX_ESCOLHA é uma pseucostante para tamanhos char, para opções de sim ou não.
#define TAMMAX_TIPOEND 8
//TAMMAX_TIPOEND é uma pseucostante para o tipo de endereço.


struct st_pessoa{
    char nome[TAMMAX_NOME], tipoEndereco[TAMMAX_TIPOEND];
    int ehFixo;
};

struct st_agenda{
    struct st_pessoa contato[TAMMAX_AGENDA];
}agenda, aux;

void selecionarTipoEnd(int tipoEndNum, int total){
    switch (tipoEndNum){
    case 1:
        strcpy(agenda.contato[total].tipoEndereco, "Alameda");
        break;
    case 2: 
        strcpy(agenda.contato[total].tipoEndereco, "Avenida");
        break;
    case 3: 
        strcpy(agenda.contato[total].tipoEndereco, "Praça");
        break;
    case 4: 
        strcpy(agenda.contato[total].tipoEndereco, "Rua");
        break;
    case 5: 
        strcpy(agenda.contato[total].tipoEndereco, "Travessa");
        break;
    default:
        break;
    }
}

int lerContatos(int *total){
    int parar = FALSE, tipoEndNum;
    char opcao[TAMMAX_ESCOLHA];

    while (parar != TRUE){
        printf("Digite seu nome: ");
        getchar();
        fgets(agenda.contato[*total].nome, TAMMAX_NOME-1, stdin);
        agenda.contato[*total].nome[strcspn(agenda.contato[*total].nome, "\n")] = 0;

        printf("[1] Alameda \n");
        printf("[2] Avenida \n");
        printf("[3] Praça \n");
        printf("[4] Rua \n");
        printf("[5] Travessa \n");
        printf("Digite o tipo do endereço: ");

        do{
            scanf("%i", &tipoEndNum);
            if( (tipoEndNum > 5) || (tipoEndNum < 0) ){
                printf("Fora de alcance! Digite novamente.\n");
            }

        }while( (tipoEndNum > 5) || (tipoEndNum < 0) );
        selecionarTipoEnd(tipoEndNum, *total);

        printf("Deseja adicionar mais alguém? (S/N): \n");
        getchar();
        scanf("%c", &opcao);
        if (toupper(opcao[0]) == 'N'){
            parar = TRUE;
        }
        getchar();
        
        (*total)++;
    }
        return *total;

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

void modificarContato(int *total){
    int pos;
    printf("Digite o número do contato que deseja alterar: \n");

    for (int i = 0; i < *total; i++){
        printf("[%i] Nome: %s\n", i, agenda.contato[i].nome);
    }
    
    scanf("%i", &pos);

    return (*total)--;
}



void mostrarContatos(int total){
    if (total == 0){
        printf("Ainda não há contatos registrados!\n");
        sleep(1);
    }else{
        printf("\n=========== DADOS ===========\n");
        for (int c = 0; c < total; c++){
            printf("\n=========== CONTATO %i ===========\n", (c+1));
            printf("Nome: %s\n", agenda.contato[c].nome);
            printf("Tipo do Endereço: %s\n", agenda.contato[c].tipoEndereco);

            printf("\n");
        }

    }

}

int main(int argc, char const *argv[]){

    int opcao = 0, totalContatos = 0; /* A variável 'totalContatos' será armazenada em um arquivo
                                       que servirá de contador, ao ler o arquivo.*/
    while(opcao != 4){
        printf("*********** AGENDA ***********\n");
        printf("1. Ver Agenda\n");
        printf("2. Adicionar Contatos\n");
        printf("3. Excluir Contatos\n");
        printf("4. Sair\n");
        printf("\nEscolha a opção: ");
        scanf("%i", &opcao);

        system("clear");

        switch (opcao){
        case 1:
            mostrarContatos(totalContatos);
            break;
        case 2:
            lerContatos(&totalContatos);
            system("clear");
            break;
        case 3:
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
    return 0;
}




