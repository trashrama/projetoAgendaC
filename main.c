#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0

//NUMOPCOES_END é uma pseuconstante para o número de opções enumeradas do endereço.
#define NUMOPCOES_END 6
//NUMOPCOES_CTT é uma pseuconstante para o número de opções enumeradas do contato.
#define NUMOPCOES_CTT 6
//NUMOPCOES_RS é uma pseuconstante para o número de opções enumeradas das redes sociais.
#define NUMOPCOES_RS 5

//TAMMAX_AGENDA é uma pseucostante para número máximo de contatos na agenda.
#define TAMMAX_AGENDA 5
#define TAMMAX_BUFFER 128
#define TAMMAX_NOME 50
#define TAMMAX_ENDERECO 50
#define TAMMAX_TEL 12
#define TAMMAX_EMAIL 50
//TAMMAX_RS é uma pseucostante para o nome de usuário rede social.
#define TAMMAX_RS 20
#define TAMMAX_CEP 9
#define TAMMAX_NOTA 20
//TAMMAX_LINHA_ARQ é uma pseucostante para o tamanho da linha do arquivo.
#define TAMMAX_LINHA_ARQ 500

struct st_pessoa{
    char nome[TAMMAX_NOME], endereco[TAMMAX_ENDERECO], cep[TAMMAX_CEP], telefone[TAMMAX_TEL];
    char nota[TAMMAX_NOTA], email[TAMMAX_EMAIL], redeSocial[TAMMAX_RS];
    enum {Alameda=1, Avenida, Praca, Rua, Travessa, Rodovia}tipoEndereco;
    enum {Celular=1, Comercial, Fixo, Pessoal, Fax, Personalizado}tipoContato;
    enum {Twitter=1, Facebook, Instagram, GitHub, LinkedIn}tipoRedeSocial;
    int numCasa;
};

struct st_agenda{
    struct st_pessoa contato[TAMMAX_AGENDA];
    struct st_pessoa aux;
}agenda, aux;

void limparTela();
void deixarPreto ();
void deixarVermelho ();
void deixarVerde ();
void deixarAmarelo();
void deixarAzul ();
void deixarRoxo ();
void deixarCiano ();
void deixarBranco ();
void resetarCores();
void tirarEspacos(char *string);
void deixarMinusculo(char *string);
void capitalizarStr(char *string);
void lerEmail(char* email);
void lerOpcao(char* opcao);
void lerContatos(int *total);
void excluirContato(int *total);
void editarContato(int total);
void listarContatos(int total);
void salvarArquivo(int total);
void consultarContato(int total);
void ordenarPorNome(int total);

void lerFormatStr(char var[], int tamanho, int tamanhoEhFixo);

char* printarNome(char *nome);
char* printarEnumerados(int opcao, int pos);
char* printarTel(char telefone[TAMMAX_TEL]);
char* printarCep(char cep[]);

int verificarEspacos(char *nome);
int lerSelecao(int u);
int lerNumCasa();
int lerArquivo();

int main(int argc, char const *argv[]){
    
    setlocale ( LC_ALL, "" );

    int totalContatos = lerArquivo();
    int opcao = 0; /* A variável 'totalContatos' será armazenada em um arquivo
                                       que servirá de contador, ao ler o arquivo.*/
    while(opcao != 6){
        //deixarCiano();
        printf("*********** AGENDA ***********\n");
        //deixarRoxo();
        printf("1. Ver Agenda\n");
        printf("2. Adicionar Contatos\n");
        printf("3. Editar Contato\n");
        printf("4. Consultar Contato\n");
        printf("5. Excluir Contato\n");
        printf("6. Sair\n");
        //deixarAzul();
        printf("\nEscolha a opção: ");
        //resetarCores();
        scanf("%i", &opcao);

        switch (opcao){
            case 1:
                listarContatos(totalContatos);
                break;
            case 2:
                lerContatos(&totalContatos);
                break;
            case 3:
                editarContato(totalContatos);
                break;
            case 4:
                consultarContato(totalContatos);
                break;
            case 5:
                excluirContato(&totalContatos);
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

//FUNÇÃO PARA LIMPAR TELA
void limparTela (){
    #ifdef __linux__
        system ( "clear" );
    #elif _WIN32
        system ( "cls" );
    #endif
}

//FUNÇÕES DE CORES - AUXILIARES - PS: Só funciona no terminal do linux por enquanto!
void deixarPreto () {
    #ifdef __linux__
          printf("\033[0;30m");
    #elif _WIN32
        system ( "cls" );
    #endif

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

//FUNÇÕES DE FORMATAÇÃO DE STRING
void tirarEspacos(char *string){

    int i, j;
    int TAM_STR = strlen(string);
    char stringSem[TAM_STR];
    char *token;

    //procurar espaços no meio
    strcpy(stringSem, "");
    strcpy(stringSem, string);
    strcpy(string, "");

    token = strtok(stringSem, " ");
    while (token != NULL){
        strcat(string, token);
        strcat(string, " ");
        token = strtok(NULL, " ");
    }

    //procurar espaços no começo
    for (i = 0; i < TAM_STR; i++){
        if (string[i] != ' '){
            break;
        }
    }

    //calular o novo tamanho sem os espaços do nome original
    TAM_STR = strlen(string) - i;

    //procurar espaços no final
    for (j = TAM_STR; j > 0; j--){
        if (string[j] != ' '){
            break;
        }
    }

    strcpy(stringSem, string);
    strncpy(string, &stringSem[i], j-1);
    string[j-1] = '\0';
    
} 
void deixarMinusculo(char *string){
    int TAM_STR = strlen(string);
    for (int i = 0; i < TAM_STR; i++){
        string[i] = tolower(string[i]);
    }
}
void capitalizarStr(char *string){
    int TAM_STR = strlen(string);
    int primeiraPos, contador, jaTevePreposicao;

    jaTevePreposicao = FALSE;
    primeiraPos = contador = 0;

    //capitalizando o primeiro caracter;
    string[0] = toupper(string[0]);


    //capitalizando sobrenomes
    for (int i = 0; i < TAM_STR; i++){
        if (string[i] == ' '){
            primeiraPos = i+1;
            string[primeiraPos] = toupper(string[primeiraPos]);
        }
    }

}
int verificarEspacos(char *nome){
    //essa função é necessária para verificar espaços
    //e impedir que meu programa bugue ao procurar sobrenome
    //quando as pessoas digitarem só nome
    int TAM_NOME = strlen(nome);
    int temEspaco = FALSE;
    for (int i = 0; i < TAM_NOME; i++){
        if (nome[i] == ' '){
            temEspaco = TRUE;
        }
    }
    
    return temEspaco;
}
char* printarNome(char *nome){

    char primeiroNome[20], ultimoSobrenome[20];
    
    //preciso do malloc pois vou retornar um vetor de caracteres
    char* nomeResumido = malloc(40);

    int temEspaco = verificarEspacos(nome);

    int fimPrimeiroNome, comecoSobrenome, fimSobrenome, delimSobrenome;
    int comecoPrimeiroNome = 0;

    int ehVogal = FALSE;
    int ehConsoante = FALSE;

    char vogais[] = {'a', 'e', 'i', 'o', 'u'};
    char consoantes[] = 
                        {'b', 'c', 'd', 'f', 'g', 'h',
                        'j', 'k', 'l', 'm', 'n', 'p',
                        'q', 'r', 's', 't', 'v', 'w', 
                        'x', 'y', 'z'};

    strcpy(primeiroNome, "");
    strcpy(ultimoSobrenome, "");
    //strlen conta tbm o caracter nulo, então é o total de caracteres  + \0
    int TAM_NOME = strlen(nome);


    if (temEspaco == TRUE){

        // pegar o primeiro nome
        for (int i = 1; i < TAM_NOME; i++){
            if (nome[i] == ' '){
                fimPrimeiroNome = i;
                break;
            }
        }
        /*strncpy copia uma quantidade N de caracteres, lembrar disso*/
        strncpy(primeiroNome, &nome[comecoPrimeiroNome], fimPrimeiroNome);
        primeiroNome[fimPrimeiroNome] = '\0';

        // pegar o segundo nome
        for (int i = TAM_NOME-1; TAM_NOME > 0; i--){
            if (nome[i] == ' '){
                comecoSobrenome = i+1;
                break;
            }
        }

        fimSobrenome = TAM_NOME - comecoSobrenome;
        strncpy(ultimoSobrenome, &nome[comecoSobrenome], fimSobrenome);
        ultimoSobrenome[fimSobrenome] = '\0';

        //ver se o 3 caracter do sobrenome é vogal e através disso limitar 

        for (int i = 0; i < 5; i++){
            if (vogais[i] == ultimoSobrenome[2]){
                ehVogal = TRUE;
            }
        }
        for (int i = 0; i < 21; i++){
            if (consoantes[i] == ultimoSobrenome[2]){
                ehConsoante = TRUE;
            }
        }    
        
        if(strlen(primeiroNome)>7){
            delimSobrenome = 1;
        }else{
            if(ehVogal){
                delimSobrenome = 2;
            }else if(ehConsoante){
                delimSobrenome = 3;
            }else{
                delimSobrenome = 1;
            }
        }

        sprintf(nomeResumido, "%s %.*s.", primeiroNome, delimSobrenome, ultimoSobrenome);
    }else{
        sprintf(nomeResumido, "%s", nome);
    }
    
    return nomeResumido;

}

//FUNÇÕES DE ORDENAÇÃO DA STRUCT
void ordenarPorNome(int total){
    int r;
    for (int i = 0; i < total; i++){
        for (int j = i+1; j < total; j++){
            r = strcmp(agenda.contato[i].nome, agenda.contato[j].nome);
            if (r>0){
                agenda.aux = agenda.contato[i];
                agenda.contato[i] = agenda.contato[j];
                agenda.contato[j] = agenda.aux;
            }
        }
    }
}

//FUNÇÕES DE PRINT - AUXILIARES
char* printarEnumerados(int opcao, int pos){
    const char *nomesTpEndereco[] = {"Al.", "Av.", "Pr.", "Rua", "Tr.", "Rod."};
    const char *nomesTpContato[] = {"Cel.", "Com.", "Fixo", "Pes.", "Fax", "Per."};
    const char *nomesTpRede[] = {"TWT.", "FB.", "INSTA.", "GH.", "LI."};
    pos--;
    
    // OPÇÃO 1: Enumerado dos Endereços
    // OPÇÃO 2: Enumerado dos tipos de Contato
    // OPÇÃO 3: Enumerado dos tipos de Rede Social

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
char* printarTel(char telefone[TAMMAX_TEL]){
    char ddd[4], pref[2], telpp[8], telsp[8];

    // A cadeia de caracteres 'telpp' refere-se aos quatro primeiros dígitos do número de telefone.
    // A cadeia de caracteres 'telsp' refere-se aos quatro últimos dígitos do número de telefone.
    
    char* telefoneFormatado = malloc(18);

    //Uso do malloc(18) aqui foi necessário pois:
    //Precisava retornar uma string (ou uma array de char) de 18 caracteres (17 + \0).
    
    strncpy(ddd,&telefone[0],2);
    strncpy(pref,&telefone[2],1);
    strncpy(telpp,&telefone[3],5);
    strncpy(telsp,&telefone[7],5);
    telsp[4] = telpp[4] = pref[1] = ddd[2] = '\0';

   
    sprintf(telefoneFormatado, "(%s) %s. %s-%s", ddd, pref, telpp, telsp);
    
    return telefoneFormatado;
}
char* printarCep(char cep[]){

    char cepPp[6], cepSp[5];
    char* cepFormatado = malloc(10);
    strncpy(cepPp, &cep[0],5);
    strncpy(cepSp, &cep[5],3);
    cepPp[5] = cepSp[3] = '\0';

     
    //Uso do malloc(10) aqui foi necessário pois:
    //Precisava retornar uma string (ou uma array de char) de 10 caracteres (9 + \0).
    

    sprintf(cepFormatado, "%s-%s", cepPp, cepSp);
    return cepFormatado;

}

//FUNÇÕES DE LEITURA - AUXILIARES
void lerEmail(char* email){
    int temArroba = FALSE, temPonto = FALSE, ehValido = FALSE;
    int tamanhoEmail;

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
        }else{
            printf("E-mail inválido!\n");
        }
        /* 
            A função realiza as seguintes ações:
            Percorre todos os caracteres do e-mail, buscando um '@'
            Caso ache, realiza outra verificação: Se o @ é o úlitmo caracter (que não deve ser)
            E se o @ é o primeiro caracter.

            Obedecendo assim, a lei <nome>@<domínio>

            Caso todas as condições forem verdade, ele finaliza a função com o return 0 e o valor
            de email continua como ponteiro, para ser atribuido para a struct na função
            de leitura dos dados.

            Caso contrário, ele entrará loop até as condições serem verdade.
        */
    }

}
void lerFormatStr(char var[], int tamanho, int tamanhoEhFixo){
    
    int temPontoVirgula = FALSE;
    /* 
        A função abaixo realiza a leitura de uma string, e
        a remoção do '\n' ao final desta.
    */
    char buffer[TAMMAX_BUFFER];
    strcpy(buffer, "");

    fgets(buffer, TAMMAX_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    /* 
        tamanhoEhFixo é uma variável booleana de controle para strings
        que tem que ter um tamanho fixo.
    */

    if (tamanhoEhFixo == TRUE){
        while (strlen(buffer) != tamanho-1){
            printf("Tamanho diferente que o esperado (%i) ou fora de alcance.\nDigite novamente: ", tamanho-1);
            fgets(buffer, TAMMAX_BUFFER, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
        }
    }


    // impedindo o usuário de escrever ponto e virgula e quebrar o codigo
    
    for (int i = 0; i < strlen(buffer); i++){
        if (buffer[i] == ';'){
            temPontoVirgula = TRUE;
        }
    }
    
    while (temPontoVirgula == TRUE){
        printf("Não digite ponto e vírgula.\nDigite novamente: ");
        fgets(buffer, TAMMAX_BUFFER, stdin);
        buffer[strcspn(buffer, "\n")] = 0; 

        for (int i = 0; i < strlen(buffer); i++){
            if (buffer[i] == ';'){
                temPontoVirgula = TRUE;
            }else{
                temPontoVirgula = FALSE;
            }
        }
    }
    
    
    
    tirarEspacos(buffer);
    deixarMinusculo(buffer);
    capitalizarStr(buffer);

    strcpy(var, buffer);
    strcpy(buffer, "");


}
void lerOpcao(char* opcao){
    /*
    A função lê a opção em uma variável auxiliar,
    e depois a transfere para o valor do ponteiro de opção.
    Uso: Seleção de sim ou não.

    Exemplo: - Deseja continuar? (Digite S ou N)
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
    char buffer[2];

    /*
    A variável p é o ponto de início das seleções, já que o usuário não começa a escolher do 0.
    A variável u é a última dentre as opções possíveis.
    */
    int p = 1;
    do{
        lerFormatStr(buffer, 2, TRUE);
        var = atoi(buffer);

        if( (var > u) || (var < p) ){
            printf("Fora de alcance! Digite novamente.\n");
        }

    }while( (var > u) || (var < p) );

    return var;
}
int lerNumCasa(){
    int var;
    char buffer[TAMMAX_BUFFER];

    /*
        A função "atoi" retorna o valor 0 caso não consiga
        converter a string para número. Então loopei ela
        forçando o usuário a digitar um número ao invés de uma string.
    */
    do{
        lerFormatStr(buffer, TAMMAX_BUFFER, FALSE);
        var = atoi(buffer);

        if (var == 0){
            printf("Você está digitando uma string.\nDigite um número: ");
        }
    } while (var == 0);

    return var;
}

//FUNÇÕES DE ARQUIVO
void salvarArquivo(int total){
    FILE *ptrArquivo = NULL;
    ptrArquivo = fopen ("dados.csv", "w");


    if (ptrArquivo == NULL){
        printf("Não foi possível criar o arquivo.\n");
        printf("Finalizando execução...\n");
        exit(0);
    }

    ordenarPorNome(total);

    for (int i = 0; i < total; i++){
        fprintf(ptrArquivo, "%i;", i);
        fprintf(ptrArquivo, "%s;", agenda.contato[i].nome);
        fprintf(ptrArquivo, "%i;%s;%i;%s;",agenda.contato[i].tipoEndereco, agenda.contato[i].endereco, agenda.contato[i].numCasa, agenda.contato[i].cep);
        fprintf(ptrArquivo, "%s;%i;%s;", agenda.contato[i].telefone, agenda.contato[i].tipoContato, agenda.contato[i].email);
        fprintf(ptrArquivo, "%i;%s;%s;\n", agenda.contato[i].tipoRedeSocial, agenda.contato[i].redeSocial, agenda.contato[i].nota);
    }
    fclose(ptrArquivo);
    ptrArquivo = NULL;
}
int lerArquivo(){

    FILE *ptrArquivo = NULL;
    char linha[TAMMAX_LINHA_ARQ];
    int total = 0;

    ptrArquivo = fopen ("dados.csv", "r");
    
    if (ptrArquivo == NULL){
        printf("\n* Não foi possível ler o arquivo.\n");
        printf("Assumindo que não existe arquivo.\nSerá criado do Zero. *\n\n");
        return 0;
    }

    //lê linha por linha do arquivo
    while( (fgets(linha, sizeof(linha), ptrArquivo)) != NULL){
        char* token;
        //tokeniza a linha por ponto e vírgula
        token = strtok(linha, ";");
        /*
            praticamente "pulei" o id e passei para o próximo token
            pois é mais seguro criar uma criavel que se incrementa ao invés de puxar o token como o total.
        */
        token = strtok(NULL, ";");

        //copiar nome
        strcpy(agenda.contato[total].nome, token);
        token = strtok(NULL, ";");

        //copiar tipoEndereco
        agenda.contato[total].tipoEndereco = atoi(token);
        token = strtok(NULL, ";");

        //copiar endereço
        strcpy(agenda.contato[total].endereco, token);
        token = strtok(NULL, ";");

        //copiar número da casa
        agenda.contato[total].numCasa = atoi(token);
        token = strtok(NULL, ";");

        //copiar cep
        strcpy(agenda.contato[total].cep, token);
        token = strtok(NULL, ";");

        //copiar telefone
        strcpy(agenda.contato[total].telefone, token);
        token = strtok(NULL, ";");

        //copiar tipo do contato
        agenda.contato[total].tipoContato = atoi(token);
        token = strtok(NULL, ";");

        //copiar email
        strcpy(agenda.contato[total].email, token);
        token = strtok(NULL, ";");

        //copiar o tipo rede da social
        agenda.contato[total].tipoRedeSocial = atoi(token);
        token = strtok(NULL, ";");
        
        //copiar o nome de usuário da rede social
        strcpy(agenda.contato[total].redeSocial, token);
        token = strtok(NULL, ";");

        //copiar nota
        strcpy(agenda.contato[total].nota, token);
        token = strtok(NULL, ";");

        total++;
    }

    fclose(ptrArquivo);
    ptrArquivo = NULL;

    ordenarPorNome(total);
    return total;
}

//FUNÇÕES PRINCIPAIS
void lerContatos(int *total){
    int parar = FALSE;
    char opcao;

    //buffer é uma variável que o email será inserido temporariamente.
    char buffer[TAMMAX_EMAIL];

    if (*total >= TAMMAX_AGENDA){
        printf("Não é possível registrar mais contatos!\nTOTAL ATINGIDO!\n\n");
    }else{

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
            printf("[6] Rodovia \n");

            printf("Digite o tipo do endereço: ");
            agenda.contato[i].tipoEndereco = lerSelecao(NUMOPCOES_END);
            

            // LEITURA DO ENDEREÇO
            printf("Digite seu endereço: ");
            lerFormatStr(agenda.contato[i].endereco, TAMMAX_ENDERECO, FALSE);

            // LEITURA DO NÚMERO DA CASA
            printf("Digite o número da casa: ");
            agenda.contato[i].numCasa = lerNumCasa();

            // LEITURA DO CEP
            printf("Digite seu CEP: ");
            lerFormatStr(agenda.contato[i].cep, TAMMAX_CEP, TRUE);


            //LEITURA DO NÚMERO DE TELEFONE
            printf("Digite o número do telefone (com DDD): ");
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
            lerEmail(&buffer);
            strcpy(agenda.contato[i].email, buffer);

            // LEITURA DA NOME DE USUÁRIO DA REDE SOCIAL
            printf("[1] Twitter \n");
            printf("[2] Facebook \n");
            printf("[3] Instagram \n");
            printf("[4] GitHub \n");
            printf("[5] LinkedIn \n");
            printf("Digite o tipo da rede social: ");
            agenda.contato[i].tipoRedeSocial = lerSelecao(NUMOPCOES_RS);

            printf("Digite o seu nome de usuário do %s: ", printarEnumerados(3, agenda.contato[i].tipoRedeSocial));
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


        ordenarPorNome(*total);
        salvarArquivo(*total);
    }
}
void excluirContato(int *total){
    int pos;
    char opcao[2];

    while (opcao[0] != 'S'){
        for (int i = 0; i < *total; i++){
            printf("[%i] Nome: %s\n", i+1, agenda.contato[i].nome);
        }

        printf("Digite o número do contato que deseja excluir: ");
        scanf("%i", &pos);
        pos = lerSelecao(*total);

        printf("Deseja confirmar a exclusão de %s? (S/N): ", printarNome(agenda.contato[pos].nome));
        getchar();
        lerOpcao(&opcao);
    }

    for (int i = pos; i < *total; i++){
        agenda.contato[i] = agenda.contato[i+1];
    }

    printf("Contato excluído!\n");

    (*total)--;
    salvarArquivo(*total);
}
void editarContato(int total){
    
    int ctt, opcao;
    int contadorOpcoes = 1;

    char conf[2];
    strcpy(conf, "");
    
    char nome[TAMMAX_NOME], endereco[TAMMAX_ENDERECO], cep[TAMMAX_CEP], telefone[TAMMAX_TEL];
    char nota[TAMMAX_NOTA], email[TAMMAX_EMAIL], redeSocial[TAMMAX_RS];
    enum {Alameda=1, Avenida, Praca, Rua, Travessa, Rodovia}tipoEndereco;
    enum {Celular=1, Comercial, Fixo, Pessoal, Fax, Personalizado}tipoContato;
    enum {Twitter=1, Facebook, Instagram, GitHub, LinkedIn}tipoRedeSocial;
    int numCasa;


    char* editaveis[50] = 
    {
        "Nome", "Tipo do Endereço", "Endereco", "Número da Casa", "CEP", "Número do Telefone",
        "Tipo de Contato", "E-Mail", "Tipo da Rede Social", "Usuário da Rede Social", "Nota"            
    };


    for (int i = 0; i < total; i++){
        printf("[%i] Nome: %s\n", i+1, agenda.contato[i].nome);
    }

    printf("Digite o número do contato que deseja alterar: \n");
    getchar();
    ctt = lerSelecao(total);
    ctt--;

    printf("\n");
    for (int i = 0; i < 11; i++){
        printf("[%i] %s\n", contadorOpcoes, editaveis[i]);
        contadorOpcoes++;
    }

    printf("\nDigite a opção desejada para editar: ");
    opcao = lerSelecao(contadorOpcoes);
    printf("\n");
    
    switch (opcao){
    case 1:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite seu nome: ", ctt+1);
            lerFormatStr(nome, TAMMAX_NOME, FALSE);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }

        strcpy(agenda.contato[ctt].nome, "");
        strcpy(agenda.contato[ctt].nome, nome);
        break;

    case 2:
        while (conf[0] != 'S'){
            printf("[1] Alameda \n");
            printf("[2] Avenida \n");
            printf("[3] Praça \n");
            printf("[4] Rua \n");
            printf("[5] Travessa \n");
            printf("[6] Rodovia \n");
            printf("[CONTATO: %i] Digite o tipo do endereço: ", ctt+1);
            tipoEndereco = lerSelecao(NUMOPCOES_END);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        agenda.contato[ctt].tipoEndereco = tipoEndereco;
        break;

    case 3:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite seu endereço: ", ctt+1);
            lerFormatStr(endereco, TAMMAX_ENDERECO, FALSE);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].endereco, "");
        strcpy(agenda.contato[ctt].endereco, endereco);
        break;

    case 4:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite o número da sua casa: ", ctt+1);
            scanf("%i", &numCasa);
            getchar();
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        agenda.contato[ctt].numCasa = numCasa;
        break;

    case 5:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite seu CEP: ", ctt+1);
            lerFormatStr(cep, TAMMAX_CEP, TRUE);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].cep, "");
        strcpy(agenda.contato[ctt].cep, cep);
        break;

    case 6:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite seu telefone: ", ctt+1);
            lerFormatStr(telefone, TAMMAX_TEL, TRUE);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].telefone, "");
        strcpy(agenda.contato[ctt].telefone, telefone);
        break;

    case 7:
        while (conf[0] != 'S'){
            printf("[1] Celular \n");
            printf("[2] Comercial \n");
            printf("[3] Fixo \n");
            printf("[4] Pessoal \n");
            printf("[5] Fax \n");
            printf("[6] Personalizado \n");
            printf("[CONTATO: %i] Digite o tipo de contato: ", ctt+1);
            getchar();
            tipoContato = lerSelecao(NUMOPCOES_END);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        agenda.contato[ctt].tipoContato = tipoContato;
        break;

    case 8:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite o seu email: ", ctt+1);
            getchar();
            lerEmail(&email);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].email, "");
        strcpy(agenda.contato[ctt].email, email);
        break;

    case 9:
        while (conf[0] != 'S'){
            printf("[1] Twitter \n");
            printf("[2] Facebook \n");
            printf("[3] Instagram \n");
            printf("[4] GitHub \n");
            printf("[5] LinkedIn \n");
            printf("[CONTATO: %i] Digite o tipo da rede social: ", ctt+1);
            tipoRedeSocial = lerSelecao(NUMOPCOES_RS);
            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        agenda.contato[ctt].tipoRedeSocial = tipoRedeSocial;
        break;

   case 10:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite o seu nome de usuário do %s: ", ctt+1, printarEnumerados(3, agenda.contato[ctt].tipoRedeSocial));
            lerFormatStr(redeSocial, TAMMAX_RS, FALSE);

            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].redeSocial, "");
        strcpy(agenda.contato[ctt].redeSocial, redeSocial);
        break;

    case 11:
        while (conf[0] != 'S'){
            printf("[CONTATO: %i] Digite uma nota: ", ctt+1);
            lerFormatStr(nota, TAMMAX_NOTA, FALSE);

            printf("Confirma a modificação? (S/N): ");
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].nota, "");
        strcpy(agenda.contato[ctt].nota, nota);
        break;

    default:
        break;
    }

    ordenarPorNome(ctt);
    salvarArquivo(total);
    printf("Alteração Feita!\n");
    printf("\n");
}
void listarContatos(int total){
    if (total == 0){
        printf("Ainda não há contatos registrados!\n");
        sleep(1);
    }else{
        printf("\n============ DADOS ============\n");
        printf("\n");
        for (int c = 0; c < total; c++){
            printf("=========== CONTATO %i ===========\n", (c+1));
            printf("Nome: %s\n", printarNome(agenda.contato[c].nome));
            printf("Endereço: %s %s, nº %i\n", printarEnumerados(1, agenda.contato[c].tipoEndereco), agenda.contato[c].endereco, agenda.contato[c].numCasa);
            printf("CEP: %s\n", printarCep(agenda.contato[c].cep));
            printf("Telefone: %s\n", printarTel(agenda.contato[c].telefone));
            printf("Tipo do Contato: %s\n", printarEnumerados(2, agenda.contato[c].tipoContato));
            printf("E-mail: %s\n", agenda.contato[c].email);
            printf("%s: %s\n", printarEnumerados(3, agenda.contato[c].tipoRedeSocial), agenda.contato[c].redeSocial);
            printf("Nota: %s\n", agenda.contato[c].nota);
        }

    }
}
void consultarContato(int total){
    char nomeConsultado[TAMMAX_NOME];
    char aux[TAMMAX_NOME];
    int r;
    
    printf("Digite o nome a ser consultado: ");
    getchar();
    lerFormatStr(nomeConsultado, TAMMAX_NOME, FALSE);

    for (int i = 0; i < total; i++){
        r = strcmp(agenda.contato[i].nome, nomeConsultado);
        if (r == 0){
            printf("Encontrado!\n\n");
            printf("Nome: %s\n", printarNome(agenda.contato[i].nome));
            printf("Endereço: %s %s, nº %i\n", printarEnumerados(1, agenda.contato[i].tipoEndereco), agenda.contato[i].endereco, agenda.contato[i].numCasa);
            printf("CEP: %s\n", printarCep(agenda.contato[i].cep));
            printf("Telefone: %s\n", printarTel(agenda.contato[i].telefone));
            printf("Tipo do Contato: %s\n", printarEnumerados(2, agenda.contato[i].tipoContato));
            printf("Email: %s\n", agenda.contato[i].email);
            printf("%s: %s\n", printarEnumerados(3, agenda.contato[i].tipoRedeSocial), agenda.contato[i].redeSocial);
            printf("Nota: %s\n", agenda.contato[i].nota);
        }else{
            printf("Nome não encontrado.\n");
        }

    }
    
}

/* unicamente, por: SANT! */
