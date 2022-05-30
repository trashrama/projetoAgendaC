#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define TAMMAX_AGENDA 5
//TAMMAX_AGENDA é uma pseucostante para número máximo de contatos na agenda.
#define TAMMAX_NOME 50
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
#define TAMMAX_CEP 10
#define TAMMAX_NOTA 200

struct st_pessoa{
    char nome[TAMMAX_NOME], tipoEndereco[TAMMAX_TIPOEND], endereco[TAMMAX_ENDERECO], cep[TAMMAX_CEP], telefone[TAMMAX_TEL], tipoContato[TAMMAX_TIPOCONT];
    char nota[TAMMAX_NOTA], email[TAMMAX_EMAIL], redeSocial[TAMMAX_SM], tipoRedeSocial[TAMMAX_TIPOSM];
    //enum tipoEndereco{Alameda = 1, Avenida, Praça, Rua};

    int numCasa;
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

void selecionarTipoSM(int tipoRedeSocial, int total){
        switch (tipoRedeSocial){
    case 1:
        strcpy(agenda.contato[total].tipoRedeSocial, "Twitter");
        break;
    case 2: 
        strcpy(agenda.contato[total].tipoRedeSocial, "Facebook");
        break;
    case 3: 
        strcpy(agenda.contato[total].tipoRedeSocial, "Instagram");
        break;
    case 4: 
        strcpy(agenda.contato[total].tipoRedeSocial, "GitHub");
        break;
    case 5: 
        strcpy(agenda.contato[total].tipoRedeSocial, "LinkedIn");
        break;
    default:
        break;
    }
}

void lerEmail(int total){
    int temArroba = FALSE, temPonto = FALSE, ehValido = FALSE;
    int tamanhoEmail;

    char email[TAMMAX_EMAIL];

    while( ehValido == FALSE ){
        printf("Digite seu e-mail: ");
        lerFormatStr(email, TAMMAX_EMAIL);
        tamanhoEmail = strlen(email);
        
        for (int i = 0; i <= tamanhoEmail; i++){
            if (email[i] == '@'){
                if ( (email[i+1] != '\0') && (i != 0) ){
                    temArroba = TRUE;
                }
            }
            if (email[i] == '.'){
                if ( (email[i+1] != '\0') && (i != 0) ){
                    temPonto = TRUE;
                }
            }
        }

        if ( (temArroba == TRUE) && (temPonto == TRUE) ){
            ehValido = TRUE;
            strcpy(agenda.contato[total].email, email);
        }else{
            printf("E-mail inválido!\n");
        }
        /* 
            A função realiza as seguintes ações:
            Percorre todos os caracteres do e-mail, buscando um '@'
            Caso ache, realiza outra verificação: Se o @ é o úlitmo caracter (que não deve ser)
            E se o @ é o primeiro caracter.

            Obedecendo assim, a lei <nome>@<domínio>

            Caso todas as condições forem verdade, ele copia a variável temporária 'email'
            para o atributo email da struct contato, e finaliza a função com o return 0.

            Caso contrário, ele entrará loop até as condições serem verdade.
        */
    }

}

int lerSelecao(){
    int var;
    do{
        scanf("%i", &var);
        if( (var > 5) || (var < 0) ){
            printf("Fora de alcance! Digite novamente.\n");
        }
    }while( (var > 5) || (var < 0) );

    return var;
}

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

void lerOpcao(char* opcao){
    
    /*
    
    A função lê a opção em uma variável auxiliar,
    e depois a transfere para o valor do ponteiro de opção.
    
    */
    char buffer;
    scanf("%c", &buffer);
    buffer = toupper(buffer);

    while ( (buffer != 'S') && (buffer != 'N') ){
        printf("Opção Inválida!\nDigite novamente: ");
        getchar();
        scanf("%c", &buffer);
        buffer = toupper(buffer);
    }
    *opcao = buffer;
}

int lerContatos(int *total){
    int parar = FALSE, ehValido = FALSE, tipoEndNum, tipoContNum, tipoRedeSocial;
    char opcao;

    while (parar != TRUE){

        int i = *total;
        // LEITURA DO NOME
        printf("Digite seu nome: ");
        getchar();
        lerFormatStr(agenda.contato[i].nome, TAMMAX_NOME);

        // LEITURA DO TIPO DO ENDEREÇO
        printf("[1] Alameda \n");
        printf("[2] Avenida \n");
        printf("[3] Praça \n");
        printf("[4] Rua \n");
        printf("[5] Travessa \n");
        printf("Digite o tipo do endereço: ");
        tipoEndNum = lerSelecao();
        selecionarTipoEnd(tipoEndNum, i);

        // LEITURA DO ENDEREÇO
        printf("Digite seu endereço: ");
        getchar();
        lerFormatStr(agenda.contato[i].endereco, TAMMAX_ENDERECO);

        // LEITURA DO CEP
        printf("Digite seu CEP: ");
        lerFormatStr(agenda.contato[i].cep, TAMMAX_CEP);

        // LEITURA DO NÚMERO DA CASA
        printf("Digite o número da casa: ");
        getchar();
        scanf("%i", &agenda.contato[i].numCasa);

        //LEITURA DO NÚMERO DE TELEFONE
        printf("Digite o número do telefone: ");
        getchar();
        lerFormatStr(agenda.contato[i].telefone, TAMMAX_TEL);
        while ( ehValido == FALSE ){
            if (strlen(agenda.contato[i].telefone) == TAMMAX_TEL-2){
                ehValido = TRUE;
            }else{
                printf("O Telefone tem que ter 11 dígitos.\nDigite novamente: ");
                lerFormatStr(agenda.contato[i].telefone, TAMMAX_TEL);
            }
        }

        //LEITURA DO TIPO DE CONTATO
        printf("[1] Celular \n");
        printf("[2] Comercial \n");
        printf("[3] Fixo \n");
        printf("[4] Pessoal \n");
        printf("[5] Fax \n");
        printf("[6] Personalizado \n");
        printf("Digite o tipo do contato: ");

        tipoContNum = lerSelecao();
        selecionarTipoCont(tipoContNum, i);
        getchar();

        // LEITURA DO E-MAIL
        lerEmail(*total);

        // LEITURA DA NOME DE USUÁRIO DA REDE SOCIAL
        printf("[1] Twitter \n");
        printf("[2] Facebook \n");
        printf("[3] Instagram \n");
        printf("[4] GitHub \n");
        printf("[5] LinkedIn \n");
        printf("Digite o tipo da rede social: ");

        tipoRedeSocial = lerSelecao();
        selecionarTipoSM(tipoRedeSocial, i);

        printf("Digite o seu nome de usuário do %s: ", agenda.contato[*total].tipoRedeSocial);
        getchar();
        lerFormatStr(agenda.contato[i].redeSocial, TAMMAX_SM);

        // LEITURA DA NOTA
        printf("Deseja adicionar uma nota? (S/N): ");
        lerOpcao(&opcao);

        if (opcao == 'N'){
            strcpy(agenda.contato[i].nota, " ");
        }else{
            printf("Digite uma nota: \n");
            lerFormatStr(agenda.contato[i].nota, TAMMAX_NOTA);
        }

        // LEITURA DE CONTINUAÇÃO
        printf("Deseja adicionar mais alguém? (S/N): ");
        getchar();
        lerOpcao(&opcao);
        if (opcao == 'N'){
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
    char ddd[4], pref[2], telpp[8], telsp[8];
    // A cadeia de caracteres 'telpp' refere-se aos quatro primeiros dígitos do número de telefone.
    // A cadeia de caracteres 'telsp' refere-se aos quatro últimos dígitos do número de telefone.
    
    strncpy(ddd,&telefone[0],2);
    strncpy(pref,&telefone[2],1);
    strncpy(telpp,&telefone[3],5);
    strncpy(telsp,&telefone[7],5);
    telsp[4] = telpp[4] = pref[1] = ddd[2] = '\0';

    printf("Telefone: (%s) %s. %s-%s\n", ddd, pref, telpp, telsp);

}

void printarCep(char cep[]){

    char cepPp[6], cepSp[5];
    strncpy(cepPp, &cep[0],5);
    strncpy(cepSp, &cep[5],3);
    cepPp[5] = cepSp[3] = '\0';
    printf("CEP: %s-%s\n", cepPp, cepSp);

}

void listarContatos(int total){
    if (total == 0){
        printf("Ainda não há contatos registrados!\n");
        sleep(1);
    }else{
        printf("\n=========== DADOS ===========\n");
        for (int c = 0; c < total; c++){
            printf("\n=========== CONTATO %i ===========\n", (c+1));
            printf("Nome: %s\n", agenda.contato[c].nome);
            printf("Endereço: %s %s, nº %i\n", agenda.contato[c].tipoEndereco, agenda.contato[c].endereco, agenda.contato[c].numCasa);
            printarCep(agenda.contato[c].cep);
            printarTel(agenda.contato[c].telefone);
            printf("Tipo do Contato: %s\n", agenda.contato[c].tipoContato);
            printf("Email: %s\n", agenda.contato[c].email);
            printf("%s: %s\n", agenda.contato[c].tipoRedeSocial, agenda.contato[c].redeSocial);
            printf("Nota: %s\n", agenda.contato[c].nota);
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
            listarContatos(totalContatos);
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




