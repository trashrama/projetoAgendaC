#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
#define TAMMAX_NOME 50
#define TAMMAX_ENDERECO 50
#define TAMMAX_TEL 12
#define TAMMAX_EMAIL 50
//TAMMAX_RS é uma pseucostante para o nome de usuário rede social.
#define TAMMAX_RS 20
#define TAMMAX_CEP 9
#define TAMMAX_NOTA 20

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
    struct st_pessoa aux;
}agenda, aux;


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
        
        

        if(ehVogal){
            delimSobrenome = 2;
        }else if(ehConsoante){
            delimSobrenome = 3;
        }else{
            delimSobrenome = 1;
        }

        sprintf(nomeResumido, "%s %.*s.", primeiroNome, delimSobrenome, ultimoSobrenome);
    }else{
        sprintf(nomeResumido, "%s", nome);
    }
    
    return nomeResumido;

}
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

    tirarEspacos(var);
    deixarMinusculo(var);
    capitalizarStr(var);

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

        // LEITURA DE CONTINUAÇÃO
        printf("Deseja adicionar mais alguém? (S/N): ");
        lerOpcao(&opcao);
        if (opcao == 'N'){
            parar = TRUE;
        }
        getchar();
        
        (*total)++;
    }

}
void listarContatos(int total){
    if (total == 0){
        printf("Ainda não há contatos registrados!\n");
        sleep(1);
    }else{
        printf("\n=========== DADOS ===========\n");
        for (int c = 0; c < total; c++){
            printf("\n=========== CONTATO %i ===========\n", (c+1));
            printf("Nome: %s\n", printarNome(agenda.contato[c].nome));
            printf("\n");
        }

    }

}

//FUNÇÕES DE ARQUIVO

void salvarArquivo(int total){
    FILE *ptrArquivo = NULL;
    ptrArquivo = fopen ( "dados.csv", "w" );

    if (ptrArquivo == NULL){
        printf("Não foi possível criar o arquivo.\n");
        printf("Finalizando execução...\n");
        exit ( 0 );
    }


    int total = 3;


    for (int i = 0; i < total; i++){
        fprintf ( ptrArquivo, "%s;%s;%s\n", agenda.contato[i].nome, agenda.contato[i].endereco, agenda.contato[i].cep);

    }

    fclose (ptrArquivo );
    ptrArquivo = NULL;

}


int main(int argc, char const *argv[]){

    int opcao = 0, totalContatos = 0; /* A variável 'totalContatos' será armazenada em um arquivo
                                       que servirá de contador, ao ler o arquivo.*/
    while(opcao != 6){
       // deixarCiano();
        printf("*********** AGENDA ***********\n");
        //deixarRoxo();
        printf("1. Ver Agenda\n");
        printf("2. Adicionar Contatos\n");
        printf("3. Consultar Contato\n");
        printf("4. Editar Contato\n");
        printf("5. Excluir Contato\n");
        printf("6. Sair\n");
       // deixarAzul();
        printf("\nEscolha a opção: ");
        //resetarCores();
        scanf("%i", &opcao);

        switch (opcao){
        case 1:
            ordenarPorNome(totalContatos);
            listarContatos(totalContatos);
            break;
        case 2:
            lerContatos(&totalContatos);
            break;
        case 3:
           // editarContato(totalContatos);
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
