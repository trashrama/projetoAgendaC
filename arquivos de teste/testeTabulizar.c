#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

//NUMOPCOES_END é uma pseuconstante para o número de opções enumeradas do endereço.
#define NUMOPCOES_END 5
//NUMOPCOES_CTT é uma pseuconstante para o número de opções enumeradas do contato.
#define NUMOPCOES_CTT 6
//NUMOPCOES_RS é uma pseuconstante para o número de opções enumeradas das redes sociais.
#define NUMOPCOES_RS 5

//TAMMAX_AGENDA é uma pseucostante para número máximo de contatos na agenda.
#define TAMMAX_AGENDA 5
#define TAMMAX_NOME 50
#define TAMMAX_ENDERECO 50
#define TAMMAX_TEL 12
#define TAMMAX_EMAIL 50
//TAMMAX_RS é uma pseucostante para o nome de usuário rede social.
#define TAMMAX_RS 20
#define TAMMAX_CEP 9
#define TAMMAX_NOTA 200

struct st_pessoa{
    char nome[TAMMAX_NOME], endereco[TAMMAX_ENDERECO], cep[TAMMAX_CEP], telefone[TAMMAX_TEL];
    char nota[TAMMAX_NOTA], email[TAMMAX_EMAIL], redeSocial[TAMMAX_RS];
    enum tipoEndereco{Alameda=1, Avenida, Praca, Rua, Travessa, Rodovia}tipoEndereco;
    enum tipoContato{Celular=1, Comercial, Fixo, Pessoal, Fax, Personalizado}tipoContato;
    enum tipoRedeSocial{Twitter=1, Facebook, Instagram, GitHub, LinkedIn}tipoRedeSocial;
    int numCasa;
};

struct st_agenda{
    struct st_pessoa contato[TAMMAX_AGENDA];
}agenda, aux;

//FUNÇÕES DE CORES - AUXILIARES
void deixarPreto () {
  printf("\033[0;30m");
}
void deixarVermelho () {
  printf("\033[1;31m");
}
void deixarVerde () {
  printf("\033[1;32m");
}
void deixarAmarelo() {
  printf("\033[1;33m");
}
void deixarAzul () {
  printf("\033[0;34m");
}
void deixarRoxo () {
  printf("\033[1;35m");
}
void deixarCiano () {
  printf("\033[1;36m");
}
void deixarBranco () {
  printf("\033[1;37m");
}
void resetarCores() {
  printf("\033[0m");
}

//FUNÇÕES DE PRINT - AUXILIARES
char* printarEnumerados(int opcao, int pos){
    const char *nomesTpEndereco[] = {"Alameda", "Avenida", "Praça", "Rua", "Travessa", "Rodovia"};
    const char *nomesTpContato[] = {"Celular", "Comercial", "Fixo", "Pessoal", "Fax", "Personalizado"};
    const char *nomesTpRede[] = {"Twitter", "Facebook", "Instagram", "GitHub", "LinkedIn"};
    pos--;
    
    // OPÇÃO 1: Enumerado dos Endereços
    // OPÇÃO 2: Enumerado dos tipos de Contato
    // OPÇÃO 3: Enumerado dos tipos de rede

    switch (opcao){
    case 1:
        return (nomesTpEndereco[pos]);
        break;
    case 2:
        return (nomesTpContato[pos]);
        break;
    case 3:
        return (nomesTpRede[pos]);
        break;
    default:
        break;
    }
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

//FUNÇÕES DE LEITURA - AUXILIARES
void lerEmail(int total){
    int temArroba = FALSE, temPonto = FALSE, ehValido = FALSE;
    int tamanhoEmail;

    char email[TAMMAX_EMAIL];

    while( ehValido == FALSE ){
        printf("Digite seu e-mail: ");
        lerFormatStr(email, TAMMAX_EMAIL, FALSE);
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
void lerFormatStr(char var[], int tamanho, int tamanhoEhFixo){
    fgets(var, tamanho, stdin);
    var[strcspn(var, "\n")] = 0;

    if (tamanhoEhFixo == TRUE){
        while (strlen(var) != tamanho-1){
            printf("Tamanho menor que o esperado (%i)\nDigite novamente: ", tamanho-1);
            fgets(var, tamanho, stdin);
            var[strcspn(var, "\n")] = 0;
        }
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
int lerSelecao(int u){
    int var;
    //A variável p é o ponto de início das seleções, já que o usuário não começa a escolher do 0.  
    int p = 1;
    do{
        scanf("%i", &var);
        if( (var > u) || (var < p) ){
            printf("Fora de alcance! Digite novamente.\n");
        }
    }while( (var > u) || (var < p) );

    return var;
}

//FUNÇÕES PRINCIPAIS
void lerContatos(int *total){
    int parar = FALSE;
    char opcao;

    while (parar != TRUE){

        int i = *total;

        // LEITURA DO NOME
        printf("Digite seu nome: ");
        getchar();
        lerFormatStr(agenda.contato[i].nome, TAMMAX_NOME, FALSE);

        // LEITURA DO TIPO DO ENDEREÇO
        printf("[1] Alameda \n");
        printf("[2] Avenida \n");
        printf("[3] Praça \n");
        printf("[4] Rua \n");
        printf("[5] Travessa \n");
        printf("Digite o tipo do endereço: ");
        agenda.contato[i].tipoEndereco = lerSelecao(NUMOPCOES_END);
        

        // LEITURA DO ENDEREÇO
        printf("Digite seu endereço: ");
        getchar();
        lerFormatStr(agenda.contato[i].endereco, TAMMAX_ENDERECO, FALSE);

        // LEITURA DO CEP
        printf("Digite seu CEP: ");
        lerFormatStr(agenda.contato[i].cep, TAMMAX_CEP, TRUE);

        // LEITURA DO NÚMERO DA CASA
        printf("Digite o número da casa: ");
        getchar();
        scanf("%i", &agenda.contato[i].numCasa);

        //LEITURA DO NÚMERO DE TELEFONE
        printf("Digite o número do telefone: ");
        getchar();
        lerFormatStr(agenda.contato[i].telefone, TAMMAX_TEL, TRUE);

        //LEITURA DO TIPO DE CONTATO
        printf("[1] Celular \n");
        printf("[2] Comercial \n");
        printf("[3] Fixo \n");
        printf("[4] Pessoal \n");
        printf("[5] Fax \n");
        printf("[6] Personalizado \n");
        printf("Digite o tipo do contato: ");
        agenda.contato[i].tipoContato = lerSelecao(NUMOPCOES_CTT);

        // LEITURA DO E-MAIL
        getchar();
        lerEmail(*total);

        // LEITURA DA NOME DE USUÁRIO DA REDE SOCIAL
        printf("[1] Twitter \n");
        printf("[2] Facebook \n");
        printf("[3] Instagram \n");
        printf("[4] GitHub \n");
        printf("[5] LinkedIn \n");
        printf("Digite o tipo da rede social: ");
        agenda.contato[i].tipoRedeSocial = lerSelecao(NUMOPCOES_RS);

        printf("Digite o seu nome de usuário do %s: ", printarEnumerados(3, agenda.contato[i].tipoRedeSocial));
        getchar();
        lerFormatStr(agenda.contato[i].redeSocial, TAMMAX_RS, FALSE);

        // LEITURA DA NOTA
        printf("Deseja adicionar uma nota? (S/N): ");
        lerOpcao(&opcao);

        if (opcao == 'N'){
            strcpy(agenda.contato[i].nota, " ");
        }else{
            printf("Digite uma nota: \n");
            lerFormatStr(agenda.contato[i].nota, TAMMAX_NOTA, FALSE);
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

}

void excluirContato(int *total){
    int pos;

    printf("Digite o número do contato que deseja excluir: \n");
    scanf("%i", &pos);
    pos = pos-1;

    for (int i = pos; i < *total; i++){
        printf("%i", i);
        agenda.contato[i] = agenda.contato[i+1];
    }

}

void modificarContato(int *total){
    int pos;
    printf("Digite o número do contato que deseja alterar: \n");

    for (int i = 0; i < *total; i++){
        printf("[%i] Nome: %s\n", i, agenda.contato[i].nome);
    }
    
    scanf("%i", &pos);

    (*total)--;
}

void listarContatos(int total){
    if (total == 0){
        printf("Ainda não há contatos registrados!\n");
        sleep(1);
    }else{
        printf("\n=========== DADOS ===========\n");
        char* colunas = {"Nome", }

    }

}

int main(int argc, char const *argv[]){

    int opcao = 0, totalContatos = 0; /* A variável 'totalContatos' será armazenada em um arquivo
                                       que servirá de contador, ao ler o arquivo.*/
    while(opcao != 6){
        deixarCiano();
        printf("*********** AGENDA ***********\n");
        deixarRoxo();
        printf("1. Ver Agenda\n");
        printf("2. Adicionar Contatos\n");
        printf("3. Consultar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Excluir Contato\n");
        printf("6. Sair\n");
        deixarAzul();
        printf("\nEscolha a opção: ");
        resetarCores();
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
        case 6:
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
