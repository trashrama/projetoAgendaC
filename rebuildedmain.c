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
#define TAMMAX_ENDERECO 50
#define TAMMAX_TEL 13
#define TAMMAX_TIPOCONT 14

struct st_pessoa{
    char nome[TAMMAX_NOME], tipoEndereco[TAMMAX_TIPOEND], endereco[TAMMAX_ENDERECO], telefone[TAMMAX_TEL], tipoContato[TAMMAX_TIPOCONT];
    int ehFixo, numCasa;
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


void selecionarTipoCont(int tipoContNum, int total){
        switch (tipoContNum){
    case 1:
        strcpy(agenda.contato[total].tipoContato, "Celular");
        break;
    case 2: 
        strcpy(agenda.contato[total].tipoContato, "Comercial");
        break;
    case 3: 
        strcpy(agenda.contato[total].tipoContato, "Fixo");
        break;
    case 4: 
        strcpy(agenda.contato[total].tipoContato, "Pessoal");
        break;
    case 5: 
        strcpy(agenda.contato[total].tipoContato, "Fax");
        break;
    case 6: 
        strcpy(agenda.contato[total].tipoContato, "Personalizado");
        break;
    default:
        break;
    }
}

int lerContatos(int *total){
    int parar = FALSE, tipoEndNum, tipoContNum;
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

        printf("Digite seu endereço: ");
        getchar();
        fgets(agenda.contato[*total].endereco, TAMMAX_ENDERECO-1, stdin);
        agenda.contato[*total].endereco[strcspn(agenda.contato[*total].endereco, "\n")] = 0;

        printf("Digite o número da casa: ");
        scanf("%i", &agenda.contato[*total].numCasa);

        printf("Digite o número do telefone: ");
        getchar();
        fgets(agenda.contato[*total].telefone, TAMMAX_TEL-1, stdin);
        agenda.contato[*total].telefone[strcspn(agenda.contato[*total].telefone, "\n")] = 0;

        printf("[1] Celular \n");
        printf("[2] Comercial \n");
        printf("[3] Fixo \n");
        printf("[4] Pessoal \n");
        printf("[5] Fax \n");
        printf("[6] Personalizado \n");
        printf("Digite o tipo do contato: ");

        do{
            scanf("%i", &tipoContNum);
            if( (tipoContNum > 6) || (tipoContNum < 0) ){
                printf("Fora de alcance! Digite novamente.\n");
            }
        }while( (tipoContNum > 6) || (tipoContNum < 0) );

        selecionarTipoCont(tipoContNum, *total);


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


void printarTel(char telefone[TAMMAX_TEL]){
    char ddd[4];
    char telpp[8];     // A cadeia de caracteres 'telpp' refere-se aos quatro primeiros dígitos do número de telefone.
    char telsp[8];     // A cadeia de caracteres 'telsp' refere-se aos quatro últimos dígitos do número de telefone.
    char pref[2];

    strncpy(ddd,&telefone[0],2);
    strncpy(pref,&telefone[2],1);
    strncpy(telpp,&telefone[3],5);
    strncpy(telsp,&telefone[7],5);

    ddd[2] = '\0';
    pref[1] = '\0';
    telpp[4] = '\0';
    telsp[4] = '\0';

    printf("Telefone: (%s) %s %s-%s\n ", ddd, pref, telpp, telsp);

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
            printf("Endereço: %s %s, nº %i\n", agenda.contato[c].tipoEndereco, agenda.contato[c].endereco, agenda.contato[c].numCasa);
            printarTel(agenda.contato[c].telefone);
            printf("Tipo do Contato: %s\n", agenda.contato[c].tipoContato);

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

        switch (opcao){
        case 1:
            mostrarContatos(totalContatos);
            break;
        case 2:
            lerContatos(&totalContatos);
            break;
        case 3:
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




