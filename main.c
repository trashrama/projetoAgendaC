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
#define TAMMAX_RS 15
#define TAMMAX_CEP 9
#define TAMMAX_NOTA 20
//TAMMAX_LINHA_ARQ é uma pseucostante para o tamanho da linha do arquivo.
#define TAMMAX_LINHA_ARQ 500
//TAMMAX_DEST é uma pseudoconstante para o tamanho do destino para o arquivo de configuração.
#define TAMMAX_DEST 30

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

void deixarPretoNegrito ();
void deixarVermelhoNegrito ();
void deixarVerdeNegrito ();
void deixarAmareloNegrito ();
void deixarAzulNegrito ();
void deixarRoxoNegrito ();
void deixarCianoNegrito ();
void deixarBrancoNegrito ();

void resetarCores();
void tirarEspacos(char *string);
void deixarMinusculo(char *string);
void capitalizarStr(char *string);
void lerEmail(char* email);
void lerOpcao(char* opcao);
void lerContatos(int *total, int auto_save, int modo_cores, char *locacao_dados);
void excluirContato(int *total, int auto_save, int modo_cores, char *locacao_dados);
void editarContato(int total, int auto_save, int modo_cores, char *locacao_dados);
void listarContatos(int total, int ehTabulizada, int modo_cores);
void salvarArquivo(int total, char *locacao_dados);
void consultarContato(int total, int modo_cores);
void ordenarPorNome(int total);
void lerConfiguracoes(char* locacao_dados, int* auto_save, int* modo_cores, int* list_tabulizada);
void gravarConfiguracoes(char* locacao_dados, int auto_save, int modo_cores, int list_tabulizada);
void editarConfiguracoes(char* locacao_dados, int* auto_save, int* modo_cores, int* list_tabulizada);
void lerFormatStr(char *var, int tamanho, int tamanhoEhFixo);

char* printarNome(char *nome);
char* printarEnumerados(int opcao, int pos);
char* printarTel(char telefone[TAMMAX_TEL]);
char* printarCep(char cep[]);
char* printarEstado(int booleana);
char* tratarNomeArquivo(char *string);

int verificarEspacos(char *nome);
int lerSelecao(int u);
int lerNum();
int lerArquivo(char* locacao_dados);

int main(int argc, char const *argv[]){
    
    setlocale ( LC_ALL, "" );

    char locacao_dados[TAMMAX_DEST];
    int auto_save;
    int modo_cores;
    int list_tabulizada;
    int opcao = 0; 

    lerConfiguracoes(locacao_dados, &auto_save, &modo_cores, &list_tabulizada);

    
    int totalContatos = lerArquivo(locacao_dados);
    /* A variável 'totalContatos' será armazenada em um arquivo que servirá de contador, ao ler o arquivo. */



    while(opcao != 7){

        if(modo_cores)
        deixarVermelhoNegrito();

        printf("*********** AGENDA ***********\n");

        if(modo_cores)
        deixarAzulNegrito();

        printf("1. Listar Contatos\n");
        printf("2. Adicionar Contatos\n");
        printf("3. Editar Contato\n");
        printf("4. Consultar Contato\n");
        printf("5. Excluir Contato\n");
        printf("6. Configurações\n");
        printf("7. Sair\n");

        if(modo_cores)
        deixarRoxo();

        printf("\nEscolha a opção: ");

        if(modo_cores)
        deixarAzulNegrito();

        opcao = lerSelecao(7);

        if(modo_cores)
        resetarCores();

        switch (opcao){
            case 1:
                listarContatos(totalContatos, list_tabulizada, modo_cores);
                break;
            case 2:
                lerContatos(&totalContatos, auto_save, modo_cores, locacao_dados);
                break;
            case 3:
                editarContato(totalContatos, auto_save, modo_cores, locacao_dados);
                break;
            case 4:
                consultarContato(totalContatos, modo_cores);
                break;
            case 5:
                excluirContato(&totalContatos, auto_save, modo_cores, locacao_dados);
                break;
            case 6:
                editarConfiguracoes(locacao_dados, &auto_save, &modo_cores, &list_tabulizada);
                break;
            case 7:
                if(modo_cores)
                deixarRoxo();
                printf("Saindo do Programa...\n");
                salvarArquivo(totalContatos, locacao_dados);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
    return 0;
}

//FUNÇÕES PRINCIPAIS
void lerContatos(int *total, int auto_save, int modo_cores, char* locacao_dados){
    int parar = FALSE;
    char opcao[2];

    char nome[TAMMAX_NOME], endereco[TAMMAX_ENDERECO], cep[TAMMAX_CEP], telefone[TAMMAX_TEL];
    char nota[TAMMAX_NOTA], email[TAMMAX_EMAIL], redeSocial[TAMMAX_RS];
    enum {Alameda=1, Avenida, Praca, Rua, Travessa, Rodovia}tipoEndereco;
    enum {Celular=1, Comercial, Fixo, Pessoal, Fax, Personalizado}tipoContato;
    enum {Twitter=1, Facebook, Instagram, GitHub, LinkedIn}tipoRedeSocial;
    int numCasa;

    strcpy(nome, "");
    strcpy(endereco, "");
    strcpy(telefone, "");
    strcpy(email, "");
    strcpy(cep, "");
    strcpy(redeSocial, "");
    strcpy(nota, "");

    //buffer é uma variável que o email será inserido temporariamente.
    char buffer[TAMMAX_EMAIL];

    if(modo_cores)
    deixarVermelhoNegrito();
    printf("++++++++++++ ADIÇÃO DE CON+A+OS ++++++++++++\n");

    if (*total >= TAMMAX_AGENDA){
        if(modo_cores)
        deixarAmareloNegrito();
        printf("Não é possível registrar mais contatos!\nTOTAL ATINGIDO!\n\n");
    }else{

        while (parar != TRUE){

            int i = *total;

            // LEITURA DO NOME
            if(modo_cores)
            deixarRoxo();
            printf("Digite seu nome: ");
            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(nome, TAMMAX_NOME, FALSE);

            // LEITURA DO TIPO DO ENDEREÇO
            if(modo_cores)
            deixarRoxo();
            printf("[1] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Alameda \n");
            
            if(modo_cores)
            deixarRoxo();
            printf("[2] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Avenida \n");

            if(modo_cores)
            deixarRoxo();
            printf("[3] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Praça \n");

            if(modo_cores)
            deixarRoxo();
            printf("[4] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Rua \n");

            if(modo_cores)
            deixarRoxo();
            printf("[5] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Travessa \n");

            if(modo_cores)
            deixarRoxo();
            printf("[6] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Rodovia \n");

            if(modo_cores)
            deixarRoxo();
            printf("Digite o tipo do endereço: ");
            if(modo_cores)
            deixarAzulNegrito();
            tipoEndereco = lerSelecao(NUMOPCOES_END);

            // LEITURA DO ENDEREÇO
            if(modo_cores)
            deixarRoxo();
            printf("Digite seu endereço: ");
            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(endereco, TAMMAX_ENDERECO, FALSE);

            // LEITURA DO NÚMERO DA CASA
            if(modo_cores)
            deixarRoxo();
            printf("Digite o número da casa ( - Sem número): ");
            if(modo_cores)
            deixarAzulNegrito();
            numCasa = lerNum();

            // LEITURA DO CEP
            if(modo_cores)
            deixarRoxo();
            printf("Digite seu CEP: ");
            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(cep, TAMMAX_CEP, TRUE);

            //LEITURA DO NÚMERO DE TELEFONE
            if(modo_cores)
            deixarRoxo();
            printf("Digite o número do telefone (com DDD): ");
            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(telefone, TAMMAX_TEL, TRUE);

            //LEITURA DO TIPO DE CONTATO
            if(modo_cores)
            deixarRoxo();
            printf("[1] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Celular \n");

            if(modo_cores)
            deixarRoxo();
            printf("[2] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Comercial \n");

            if(modo_cores)
            deixarRoxo();
            printf("[3] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Fixo \n");

            if(modo_cores)
            deixarRoxo();
            printf("[4] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Pessoal \n");

            if(modo_cores)
            deixarRoxo();
            printf("[5] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Fax \n");

            if(modo_cores)
            deixarRoxo();
            printf("[6] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Personalizado \n");

            if(modo_cores)
            deixarRoxo();
            printf("Digite o tipo do contato: ");
            if(modo_cores)
            deixarRoxoNegrito();
            tipoContato = lerSelecao(NUMOPCOES_CTT);

            // LEITURA DO E-MAIL
            if(modo_cores)
            deixarRoxo();
            printf("Digite seu e-mail: ");
            if(modo_cores)
            deixarAzulNegrito();
            lerEmail(&buffer);
            strcpy(email, buffer);

            // LEITURA DA NOME DE USUÁRIO DA REDE SOCIAL
            if(modo_cores)
            deixarRoxo();
            printf("[1] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Twitter \n");

            if(modo_cores)
            deixarRoxo();
            printf("[2] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Facebook \n");

            if(modo_cores)
            deixarRoxo();
            printf("[3] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Instagram \n");

            if(modo_cores)
            deixarRoxo();
            printf("[4] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("GitHub \n");

            if(modo_cores)
            deixarRoxo();
            printf("[5] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("LinkedIn \n");

            if(modo_cores)
            deixarRoxo();
            printf("Digite o tipo da rede social: ");
            if(modo_cores)
            deixarAzulNegrito();
            tipoRedeSocial = lerSelecao(NUMOPCOES_RS);

            if(modo_cores)
            deixarRoxo();
            printf("Digite o seu nome de usuário do ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("%s: ", printarEnumerados(3, tipoRedeSocial));
            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(redeSocial, TAMMAX_RS, FALSE);

            // LEITURA DA NOTA
            if(modo_cores)
            deixarRoxo();
            printf("Deseja adicionar uma nota? (S/N): ");
            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&opcao);


            if (opcao[0] == 'N'){
                strcpy(nota, " ");
            }else{
                if(modo_cores)
                deixarRoxo();
                printf("Digite uma nota: ");
                if(modo_cores)
                deixarAzulNegrito();
                lerFormatStr(nota, TAMMAX_NOTA, FALSE);
            }

            // LEITURA DE CONTINUAÇÃO
            if(modo_cores)
            deixarRoxo();
            printf("Deseja confirmar as informações? (S/N): ");
            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&opcao);
            if (opcao[0] == 'N'){
                if(modo_cores)
                deixarRoxo();
                printf("Adição Cancelada.\n ");
                return 0;
            }else{
                //copiar nome para struct
                strcpy(agenda.contato[i].nome, nome);
                //copiar tipoEndereco para struct
                agenda.contato[i].tipoEndereco = tipoEndereco;
                //copiar endereco para struct
                strcpy(agenda.contato[i].endereco, endereco);
                //copiar num da casa
                agenda.contato[i].numCasa = numCasa;
                //copiar cep
                strcpy(agenda.contato[i].cep, cep);
                //copiar telefone
                strcpy(agenda.contato[i].telefone, telefone);
                //copiar tipoContato
                agenda.contato[i].tipoContato = tipoContato;
                //copiar e-mail
                strcpy(agenda.contato[i].email, email);
                //copiar tipo da rede social
                agenda.contato[i].tipoRedeSocial = tipoRedeSocial;
                //copiar usuario da rede social
                strcpy(agenda.contato[i].redeSocial, redeSocial);
                //copiar nota
                strcpy(agenda.contato[i].nota, nota);
            }

            if(modo_cores)
            deixarRoxo();
            printf("Deseja adicionar mais alguém? (S/N): ");
            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&opcao);
            if (opcao[0] == 'N'){
                parar = TRUE;
            }
            
            (*total)++;
        }

        
        ordenarPorNome(*total);

        if(auto_save){
            salvarArquivo(*total, locacao_dados);
        }
    }
}
void excluirContato(int *total, int auto_save, int modo_cores, char* locacao_dados){
    int pos;
    char opcao[2];

    if(modo_cores)
    deixarVermelhoNegrito();
    printf("----------EXCLUSÃO DE CONTATOS----------\n");

    while (opcao[0] != 'S'){
        for (int i = 0; i < *total; i++){
            if(modo_cores)
            deixarRoxo();
            printf("[%i] ", i+1);
            if(modo_cores)
            deixarAzulNegrito();
            printf("Nome: ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("%s\n", agenda.contato[i].nome);
        }

        if(modo_cores)
        deixarRoxo();
        printf("Digite o número do contato que deseja excluir: ");
        if(modo_cores)
        deixarAzulNegrito();
        pos = lerSelecao(*total);
        pos--;

        if(modo_cores)
        deixarRoxo();
        printf("Deseja confirmar a exclusão de ");

        if(modo_cores)
        deixarRoxoNegrito();
        printf("%s", printarNome(agenda.contato[pos].nome));

        if(modo_cores)
        deixarRoxo();
        printf("? (S/N): ");

        if(modo_cores)
        deixarAzulNegrito();
        lerOpcao(&opcao);

        if (opcao[0] == 'N'){
            printf("Edição cancelada.\n");
            return 0;
        }
        
    }

    for (int i = pos; i < *total; i++){
        agenda.contato[i] = agenda.contato[i+1];
    }

    if(modo_cores)
    deixarRoxo();
    printf("Contato excluído!\n");

    (*total)--;

    if(auto_save){
        salvarArquivo(*total, locacao_dados);
    }
}
void editarContato(int total, int auto_save, int modo_cores, char *locacao_dados){
    
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

    if(modo_cores)
    deixarVermelhoNegrito();
    printf("\^\^\^\^\^\^EDIÇÃO DE CONTATOS\^\^\^\^\^\^\n");

    for (int i = 0; i < total; i++){
        if(modo_cores)
        deixarRoxo();
        printf("[%i] ", i+1);
        if(modo_cores)
        deixarAzulNegrito();
        printf("Nome: ");
        if(modo_cores)
        deixarRoxoNegrito();
        printf("%s\n", agenda.contato[i].nome);
    }

    if(modo_cores)    
    deixarRoxo();
    printf("Digite o número do contato que deseja alterar: ");
    if(modo_cores)
    deixarAzulNegrito();

    ctt = lerSelecao(total);
    ctt--;

    printf("\n");
    for (int i = 0; i < 11; i++){
        
        if(modo_cores)
        deixarRoxoNegrito();
        printf("[%i] ", contadorOpcoes);
        if(modo_cores)
        deixarRoxo();
        printf("%s\n", editaveis[i]);
        contadorOpcoes++;
    }

    if(modo_cores)
    deixarRoxo();
    printf("Digite a opção desejada para editar: ");
    if(modo_cores)
    deixarAzulNegrito();
    opcao = lerSelecao(contadorOpcoes);
    printf("\n");
    
    switch (opcao){
    case 1:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite seu nome: ");

            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(nome, TAMMAX_NOME, FALSE);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
            
        }

        strcpy(agenda.contato[ctt].nome, "");
        strcpy(agenda.contato[ctt].nome, nome);
        break;

    case 2:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxo();
            printf("[1] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Alameda \n");
            
            if(modo_cores)
            deixarRoxo();
            printf("[2] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Avenida \n");

            if(modo_cores)
            deixarRoxo();
            printf("[3] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Praça \n");

            if(modo_cores)
            deixarRoxo();
            printf("[4] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Rua \n");

            if(modo_cores)
            deixarRoxo();
            printf("[5] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Travessa \n");

            if(modo_cores)
            deixarRoxo();
            printf("[6] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Rodovia \n");

            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();

            printf("Digite o novo tipo de endereço: ");
            tipoEndereco = lerSelecao(NUMOPCOES_END);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");
            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        agenda.contato[ctt].tipoEndereco = tipoEndereco;
        break;

    case 3:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite seu endereço: ");
            
            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(endereco, TAMMAX_ENDERECO, FALSE);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].endereco, "");
        strcpy(agenda.contato[ctt].endereco, endereco);
        break;

    case 4:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite o número da sua casa: ");


            if(modo_cores)
            deixarAzulNegrito();
            numCasa = lerNum();

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        agenda.contato[ctt].numCasa = numCasa;
        break;

    case 5:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite seu CEP: ");

            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(cep, TAMMAX_CEP, TRUE);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].cep, "");
        strcpy(agenda.contato[ctt].cep, cep);
        break;

    case 6:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite seu telefone: ", ctt+1);

            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(telefone, TAMMAX_TEL, TRUE);
            
            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].telefone, "");
        strcpy(agenda.contato[ctt].telefone, telefone);
        break;

    case 7:
        while (conf[0] != 'S'){
           if(modo_cores)
            deixarRoxo();
            printf("[1] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Celular \n");

            if(modo_cores)
            deixarRoxo();
            printf("[2] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Comercial \n");

            if(modo_cores)
            deixarRoxo();
            printf("[3] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Fixo \n");

            if(modo_cores)
            deixarRoxo();
            printf("[4] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Pessoal \n");

            if(modo_cores)
            deixarRoxo();
            printf("[5] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Fax \n");

            if(modo_cores)
            deixarRoxo();
            printf("[6] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Personalizado \n");

            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite o tipo de contato: ");

            if(modo_cores)
            deixarAzulNegrito();
            tipoContato = lerSelecao(NUMOPCOES_END);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        agenda.contato[ctt].tipoContato = tipoContato;
        break;

    case 8:
        while (conf[0] != 'S'){

            if(modo_cores)
            deixarRoxo();
            printf("Digite o seu email: ");

            if(modo_cores)
            deixarAzulNegrito();
            lerEmail(&email);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].email, "");
        strcpy(agenda.contato[ctt].email, email);
        break;

    case 9:
        while (conf[0] != 'S'){
             if(modo_cores)
            deixarRoxo();
            printf("[1] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Twitter \n");

            if(modo_cores)
            deixarRoxo();
            printf("[2] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Facebook \n");

            if(modo_cores)
            deixarRoxo();
            printf("[3] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("Instagram \n");

            if(modo_cores)
            deixarRoxo();
            printf("[4] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("GitHub \n");

            if(modo_cores)
            deixarRoxo();
            printf("[5] ");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("LinkedIn \n");


            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite o tipo da rede social: ");
            if(modo_cores)
            deixarAzulNegrito();
            tipoRedeSocial = lerSelecao(NUMOPCOES_RS);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");
            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        agenda.contato[ctt].tipoRedeSocial = tipoRedeSocial;
        break;

   case 10:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite o seu nome de usuário do");
            if(modo_cores)
            deixarRoxoNegrito();
            printf("%s: ", printarEnumerados(3, tipoRedeSocial));
            
            if(modo_cores)
            deixarRoxo();
            lerFormatStr(redeSocial, TAMMAX_RS, FALSE);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");

            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].redeSocial, "");
        strcpy(agenda.contato[ctt].redeSocial, redeSocial);
        break;

    case 11:
        while (conf[0] != 'S'){
            if(modo_cores)
            deixarRoxoNegrito();
            printf("[CONTATO: %i] ", ctt+1);

            if(modo_cores)
            deixarRoxo();
            printf("Digite uma nota: ");
            if(modo_cores)
            deixarAzulNegrito();
            lerFormatStr(nota, TAMMAX_NOTA, FALSE);

            if(modo_cores)
            deixarRoxo();
            printf("Confirma a modificação? (S/N): ");
            if(modo_cores)
            deixarAzulNegrito();
            lerOpcao(&conf);
        }
        strcpy(agenda.contato[ctt].nota, "");
        strcpy(agenda.contato[ctt].nota, nota);
        break;

    default:
        break;
    }

    ordenarPorNome(ctt);
    if(auto_save){
        salvarArquivo(total, locacao_dados);
    }
    printf("Alteração Feita!\n");
    printf("\n");
}
void listarContatos(int total, int ehTabulizada, int modo_cores){

    char subStrNome[11];
    char subStrEnd[11];
    char subStrNt[11];
    printf("\n");

    if (total == 0){
        if(modo_cores)
        deixarAmareloNegrito();
        printf("Ainda não há contatos registrados!\n");
        sleep(1);
    }else{

        if(ehTabulizada){

            if(modo_cores)
            deixarVermelhoNegrito();

            printf("============================================== LISTAGEM TABULADA ==============================================\n");
            printf("%03s|%-10s|%-3s|%-10s|%-5s|%-12s|%-3s|%-20s |%-3s|%-10s|%-10s|\n",
            "ID", "NOME", "T.E", "END.", "NUM.", "NUM PARA CONTATO ", "T.C ", "EMAIL", "R.S ", "USERNAME", "NOTA");
            
            if(modo_cores)
            deixarAzulNegrito();

            for (int c = 0; c < total; c++){
                strncpy(subStrNome, printarNome(agenda.contato[c].nome), 10);
                strncpy(subStrEnd, agenda.contato[c].endereco, 10);
                strncpy(subStrNt, agenda.contato[c].nota, 10);

                printf("%03i|%-10s|%-3s|%-10s|%-5i|%-12s|%-3s|%-20s |%-3s|%-10s|%-10s|\n\n",
                c+1, subStrNome, printarEnumerados(1, agenda.contato[c].tipoEndereco), subStrEnd, agenda.contato[c].numCasa,
                printarTel(agenda.contato[c].telefone), printarEnumerados(2, agenda.contato[c].tipoContato),
                agenda.contato[c].email, printarEnumerados(3, agenda.contato[c].tipoRedeSocial), agenda.contato[c].redeSocial,
                subStrNt);

            }
        }else{
            if(modo_cores)
            deixarVermelhoNegrito();

            printf("======== LISTAGEM LINEAR ========\n");
            printf("\n");
            for (int c = 0; c < total; c++){
                printf("=========== CONTATO"); 
                if(modo_cores)
                deixarAzulNegrito();
                printf(" %i ", (c+1));
                if(modo_cores)
                deixarVermelhoNegrito();
                printf("===========\n");

                printf("Nome: ");
                if(modo_cores)
                deixarAzulNegrito();
                printf("%s\n", printarNome(agenda.contato[c].nome));

                if(modo_cores)
                deixarVermelhoNegrito();
                printf("Endereço: ");
                if(modo_cores)
                deixarAzulNegrito();
                printf("%s %s, nº %i\n", printarEnumerados(1, agenda.contato[c].tipoEndereco), agenda.contato[c].endereco, agenda.contato[c].numCasa);
                
                if(modo_cores)
                deixarVermelhoNegrito();
                printf("CEP: ");
                if(modo_cores)
                deixarAzulNegrito();
                printf("%s\n", printarCep(agenda.contato[c].cep));

                if(modo_cores)
                deixarVermelhoNegrito();
                printf("Telefone: ");
                if(modo_cores)
                deixarAzulNegrito();
                printf("%s\n", printarTel(agenda.contato[c].telefone));
                
                if(modo_cores)
                deixarVermelhoNegrito();
                printf("Tipo do Contato: ");
                if(modo_cores)
                deixarAzulNegrito();
                printf("%s\n", printarEnumerados(2, agenda.contato[c].tipoContato));

                if(modo_cores)
                deixarVermelhoNegrito();
                printf("E-mail: ");
                if(modo_cores)
                deixarAzulNegrito();
                printf("%s\n", agenda.contato[c].email);

                if(modo_cores)
                deixarVermelhoNegrito();
                printf("%s: ",  printarEnumerados(3, agenda.contato[c].tipoRedeSocial));
                if(modo_cores)
                deixarAzulNegrito();
                printf("%s\n", agenda.contato[c].redeSocial);
                
                if(modo_cores)
                deixarVermelhoNegrito();
                printf("Nota: ");
                if(modo_cores)
                deixarAzulNegrito(); 
                printf("%s\n", agenda.contato[c].nota);

                if(modo_cores)
                deixarVermelhoNegrito();
            }
        }
    }
    printf("\n===============================\n");

    printf("\n");
}
void consultarContato(int total, int modo_cores){
    char nomeConsultado[TAMMAX_NOME];
    char* r;

    int contResultados = 0;
    // contResultados - Contador dos Resultados
    int foiEncontrado = FALSE;

    if(modo_cores)
    deixarRoxo();

    printf("Digite o nome a ser consultado: ");
    if(modo_cores)
    deixarAzulNegrito();
    lerFormatStr(nomeConsultado, TAMMAX_NOME, FALSE);

    for (int i = 0; i < total; i++){
        r = strstr(agenda.contato[i].nome, nomeConsultado);
        if (r != NULL){
            foiEncontrado = TRUE;
            contResultados++;

            if(modo_cores)
            deixarVermelhoNegrito();
            printf("\n=============================\n%18s %i\n=============================\n", "RESULTADO", contResultados);
            if(modo_cores)
            deixarAzulNegrito();
            printf(" %i ", (i+1));
            if(modo_cores)
            deixarVermelhoNegrito();
            printf("===========\n");

            printf("Nome: ");
            if(modo_cores)
            deixarAzulNegrito();
            printf("%s\n", printarNome(agenda.contato[i].nome));

            if(modo_cores)
            deixarVermelhoNegrito();
            printf("Endereço: ");
            if(modo_cores)
            deixarAzulNegrito();
            printf("%s %s, nº %i\n", printarEnumerados(1, agenda.contato[i].tipoEndereco), agenda.contato[i].endereco, agenda.contato[i].numCasa);
            
            if(modo_cores)
            deixarVermelhoNegrito();
            printf("CEP: ");
            if(modo_cores)
            deixarAzulNegrito();
            printf("%s\n", printarCep(agenda.contato[i].cep));

            if(modo_cores)
            deixarVermelhoNegrito();
            printf("Telefone: ");
            if(modo_cores)
            deixarAzulNegrito();
            printf("%s\n", printarTel(agenda.contato[i].telefone));
            
            if(modo_cores)
            deixarVermelhoNegrito();
            printf("Tipo do Contato: ");
            if(modo_cores)
            deixarAzulNegrito();
            printf("%s\n", printarEnumerados(2, agenda.contato[i].tipoContato));

            if(modo_cores)
            deixarVermelhoNegrito();
            printf("E-mail: ");
            if(modo_cores)
            deixarAzulNegrito();
            printf("%s\n", agenda.contato[i].email);

            if(modo_cores)
            deixarVermelhoNegrito();
            printf("%s: ",  printarEnumerados(3, agenda.contato[i].tipoRedeSocial));
            if(modo_cores)
            deixarAzulNegrito();
            printf("%s\n", agenda.contato[i].redeSocial);
            
            if(modo_cores)
            deixarVermelhoNegrito();
            printf("Nota: ");
            if(modo_cores)
            deixarAzulNegrito(); 
            printf("%s\n", agenda.contato[i].nota);

            if(modo_cores)
            deixarVermelhoNegrito();
            printf("=============================");
            
        }
    }

    if (foiEncontrado == FALSE){
        if(modo_cores)
        deixarRoxo();
        printf("Não há resultados.");
    }

    printf("\n");
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
    #endif

}
void deixarVermelho () {
    #ifdef __linux__
        printf("\033[0;31m");
    #endif
}
void deixarVerde () {
    #ifdef __linux__
        printf("\033[0;32m");
    #endif
}
void deixarAmarelo() {
    #ifdef __linux__
        printf("\033[0;33m");
    #endif
}
void deixarAzul() {
    #ifdef __linux__
        printf("\033[0;34m");
    #endif
}
void deixarRoxo() {
    #ifdef __linux__
        printf("\033[0;35m");
    #endif
}
void deixarCiano() {
    #ifdef __linux__
        printf("\033[0;36m");
    #endif
}
void deixarBranco() {
    #ifdef __linux__
        printf("\033[0;37m");
    #endif
}

void deixarPretoNegrito() {
    #ifdef __linux__
        printf("\033[1;30m");     
    #endif

}
void deixarVermelhoNegrito () {
    #ifdef __linux__
        printf("\033[1;31m");
    #endif
}
void deixarVerdeNegrito () {
    #ifdef __linux__
        printf("\033[1;32m");
    #endif
}
void deixarAmareloNegrito() {
    #ifdef __linux__
        printf("\033[1;33m");
    #endif
}
void deixarAzulNegrito () {
    #ifdef __linux__
        printf("\033[1;34m");
    #endif
}
void deixarRoxoNegrito () {
    #ifdef __linux__
        printf("\033[1;35m");
    #endif
}
void deixarCianoNegrito () {
    #ifdef __linux__
        printf("\033[1;36m");
    #endif
}
void deixarBrancoNegrito () {
    #ifdef __linux__
        printf("\033[1;37m");
    #endif
}

void resetarCores() {

    #ifdef __linux__
        printf("\033[0m");
    #endif
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
    const char *nomesTpRede[] = {"TWT.", "FB.", "IG.", "GH.", "LIn."};
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
        lerFormatStr(email, TAMMAX_EMAIL, FALSE);
        tamanhoEmail = strlen(email);
        
        for (int i = 0; i < tamanhoEmail; i++){
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
void lerFormatStr(char* var, int tamanho, int tamanhoEhFixo){
    
    int temPontoVirgula = FALSE;
    /* 
        A função abaixo realiza a leitura de uma string, e
        a remoção do '\n' ao final desta.
    */
    char buffer[TAMMAX_BUFFER];
    strcpy(buffer, "");

    fgets(buffer, TAMMAX_BUFFER, stdin);

    while (buffer[0] == '\n' && buffer[1] == '\0') {
        printf("Não é possível digitar uma string vazia.\nDigite novamente: ");
        fgets(buffer, TAMMAX_BUFFER, stdin);
    }
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

    char buffer[2];
    lerFormatStr(buffer, 2, TRUE);

    buffer[0] = toupper(buffer[0]);

    while ( (buffer[0] != 'S') && (buffer[0] != 'N') ){
        printf("Opção Inválida!\nDigite novamente: ");
        lerFormatStr(buffer, 2, TRUE);
        buffer[0] = toupper(buffer[0]);
    }

    strcpy(opcao, buffer);
    strcpy(buffer, "");

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
int lerNum(){
    int var;
    char buffer[TAMMAX_BUFFER];

    /*
        A função "atoi" retorna o valor 0 caso não consiga
        converter a string para número. Então loopei ela
        forçando o usuário a digitar um número ao invés de uma string.
    */
    do{
        lerFormatStr(buffer, TAMMAX_BUFFER, FALSE);
        if (buffer[0] == '-'){
            return 0;
        }
        var = atoi(buffer);

        if (var == 0){
            printf("Você está digitando uma string.\nDigite um número: ");
        }
    } while (var == 0);

    return var;
}

//FUNÇÕES DE ARQUIVO
void salvarArquivo(int total, char* locacao_dados){
    FILE *ptrArquivo = NULL;
    ptrArquivo = fopen (locacao_dados, "w");


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
int lerArquivo(char* locacao_dados){

    FILE *ptrArquivo = NULL;
    char linha[TAMMAX_LINHA_ARQ];
    int total = 0;

    ptrArquivo = fopen(locacao_dados, "r");
    
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

//FUNÇÕES DE CONFIGURAÇÃO
char* printarEstado(int booleana){
    if(booleana == 1){
        return "HABILITADO";
    }else{
        return "DESABILITADO";
    }
 
}
char* tratarNomeArquivo(char *string){

    int ultimoCaracter = strlen(string)-1;
    int temCsv = (string[ultimoCaracter] == 'v') && (string[ultimoCaracter-1] == 's') && (string[ultimoCaracter-2] == 'c') && (string[ultimoCaracter-3] == '.');
    
    //verificar se tem '.' ou espaços no nome do arquivo, e substituir por exemplo, um underline.
    //de quebra, ainda deixa tudo minúsculo xD
    for (int i = 0; i <= ultimoCaracter; i++){
        string[i] = tolower(string[i]);
        
        /* 
        
        A lógica usada aqui foi a seguinte, estou verificando se o carácter na posição i da string
        é um espaço, ou um ponto. E se for um ponto, verifica se não tem a formação de caracteres ".csv".
        para impedir que o programa transforme o ponto de ".csv" em underline.

        */

        if ( (string[i] == ' ') || ( (string[i] == '.') && !temCsv) ) {
            string[i] = '_';
        }
    }

    /*
        Basicamente, essa função vai procurar 
        por ".csv" na string e caso não tenha, vai adicionar.
    */
    
    if(!temCsv){
        strcat(string, ".csv");
    }
    

}
void lerConfiguracoes(char* locacao_dados, int* auto_save, int* modo_cores, int* list_tabulizada){

    FILE *arqConfig = NULL;
    char linha[TAMMAX_LINHA_ARQ];
    char bufferAtoi[2];

    int numLinha = 0;
    int comecoDados, fimDados;

    arqConfig = fopen ("config.ini", "r");
    
    if (arqConfig == NULL){
        arqConfig = fopen ("config.ini", "w");
        // estrutura padrao de configuração
        fprintf(arqConfig, "arquivo_dados=\"data.csv\"\n");
        fprintf(arqConfig, "auto_save=%i\n", TRUE);
        fprintf(arqConfig, "modo_cores=%i\n", FALSE);
        fprintf(arqConfig, "listagem_tabulizada=%i\n", TRUE);


        fclose(arqConfig);
        arqConfig = fopen ("config.ini", "r");

    }


    while( (fgets(linha, sizeof(linha), arqConfig) ) != NULL){

        for (int i = 0; i < strlen(linha); i++){
            if(linha[i] == '='){
                comecoDados = i+1;
                break;
            }
        }
        
        switch (numLinha){
        case 0:
            comecoDados++;
            for (int j = strlen(linha)-1; j > 0; j--){
                if(linha[j] == '"'){
                    fimDados = j-1;
                    break;
                }
            }
            strcpy(locacao_dados, "");
            strncpy(locacao_dados, &linha[comecoDados], (fimDados-comecoDados+1));
            locacao_dados[fimDados-comecoDados+1] = '\0';

            comecoDados = 0;
            fimDados = 0;

            break;
        case 1:
            strcpy(bufferAtoi, "");
            strncpy(bufferAtoi, &linha[comecoDados], 1);
            bufferAtoi[1] = '\0';

            *auto_save = atoi(bufferAtoi);
            strcpy(bufferAtoi, "");

            break;
        case 2:
            strcpy(bufferAtoi, "");
            strncpy(bufferAtoi, &linha[comecoDados], 1);
            bufferAtoi[1] = '\0';

            *modo_cores = atoi(bufferAtoi);
            strcpy(bufferAtoi, "");
            break;
        case 3:
            strcpy(bufferAtoi, "");
            strncpy(bufferAtoi, &linha[comecoDados], 1);
            bufferAtoi[1] = '\0';

            *list_tabulizada = atoi(bufferAtoi);
            strcpy(bufferAtoi, "");
            break;
        }
        numLinha++;
    }

    fclose(arqConfig);
    arqConfig = NULL;

}
void editarConfiguracoes(char* locacao_dados, int* auto_save, int* modo_cores, int* list_tabulizada){
    char opcao[2];
    char novoNomeArq[TAMMAX_DEST];
    int selecao;

    while(opcao[0] != 'N'){
        if(*modo_cores)
        deixarVermelhoNegrito();
        printf("*****[CONFIGURAÇÕES]*****\n");

        if(*modo_cores)
        deixarRoxo();
        printf("Destino dos Dados = ");

        if(*modo_cores)
        deixarRoxoNegrito();
        printf("\"%s\"\n", locacao_dados);

        if(*modo_cores)
        deixarRoxo();
        printf("Auto-Save = ");

        if(*modo_cores)
        deixarRoxoNegrito();
        printf("%s\n", printarEstado(*auto_save));

        if(*modo_cores)
        deixarRoxo();
        printf("Modo Cores = ");
        if(*modo_cores)
        deixarRoxoNegrito();
        printf("%s\n", printarEstado(*modo_cores));

        if(*modo_cores)
        deixarRoxo();
        printf("Listagem Tabulizada = ");
        if(*modo_cores)
        deixarRoxoNegrito();
        printf("%s\n\n", printarEstado(*list_tabulizada));

        if(*modo_cores)
        deixarRoxoNegrito();
        printf("Deseja editar alguma configuração? (S/N): ");
        if(*modo_cores)
        deixarAzulNegrito();
        lerOpcao(&opcao);
        
        if (opcao[0] != 'N'){

            printf("\n-------------------------------\n");
            if(*modo_cores)
            deixarRoxoNegrito();
            printf("[1] ");
            if(*modo_cores)
            deixarRoxo();
            printf("Destino dos Dados = ");
            if(*modo_cores)
            deixarRoxoNegrito();
            printf("\"%s\"\n", locacao_dados);

            if(*modo_cores)
            deixarRoxoNegrito();
            printf("[2] ");
            if(*modo_cores)
            deixarRoxo();
            printf("Auto-Save = ");
            if(*modo_cores)
            deixarRoxoNegrito();
            printf("%s\n", printarEstado(*auto_save));

            if(*modo_cores)
            deixarRoxoNegrito();
            printf("[3] ");
            if(*modo_cores)
            deixarRoxo();
            printf("Modo Cores = ");
            if(*modo_cores)
            deixarRoxoNegrito();
            printf("%s\n", printarEstado(*modo_cores));

            if(*modo_cores)
            deixarRoxoNegrito();
            printf("[4] ");
            if(*modo_cores)
            deixarRoxo();
            printf("Listagem Tabulizada = ");
            if(*modo_cores)
            deixarRoxoNegrito();
            printf("%s\n\n", printarEstado(*list_tabulizada));

            printf("Qual opção deseja selecionar?: ");
            selecao = lerSelecao(4);

            switch (selecao){
            case 1:
                if(*modo_cores)
                deixarRoxo();
                printf("Digite a novo nome do arquivo: ");

                if(*modo_cores)
                deixarAzulNegrito();
                lerFormatStr(novoNomeArq, TAMMAX_DEST-3, FALSE);
                tratarNomeArquivo(novoNomeArq);

                if(*modo_cores)
                deixarRoxo();
                printf("Confirma o novo nome do arquivo? (S/N): ");

                strcpy(opcao, "");
                if(*modo_cores)
                deixarAzulNegrito();
                lerOpcao(&opcao);
                
                if(*modo_cores)
                deixarRoxo();

                if(opcao[0] == 'S'){
                    rename(locacao_dados, novoNomeArq);
                    printf("Modificação efetuada.\n");
                    printf("Será efetiva após o reinício do programa.\n");
                    strcpy(locacao_dados, "");
                    strcpy(locacao_dados, novoNomeArq);
                }else{
                    printf("Edição cancelada.\n");
                }
                break;
            case 2:
                *auto_save = !(*auto_save);
                printf("Modificação efetuada.\n\n");
                break;
            case 3:
                *modo_cores = !(*modo_cores);
                printf("NT: Ativar modo cores no Windows não fará qualquer diferença.\n");
                printf("Modificação efetuada.\n\n");
                break;
            case 4:
                *list_tabulizada = !(*list_tabulizada);
                printf("Modificação efetuada.\n\n");
                break;
            default:
                break;
            }
            printf("\n");
            gravarConfiguracoes(locacao_dados, *auto_save, *modo_cores, *list_tabulizada);

        }
    }
}
void gravarConfiguracoes(char* locacao_dados, int auto_save, int modo_cores, int list_tabulizada){
    FILE *arqConfig = NULL;
    arqConfig = fopen ("config.ini", "w");

    fprintf(arqConfig, "arquivo_dados=\"%s\"\n", locacao_dados);
    fprintf(arqConfig, "auto_save=%i\n", auto_save);
    fprintf(arqConfig, "modo_cores=%i\n", modo_cores);
    fprintf(arqConfig, "listagem_tabulizada=%i\n", list_tabulizada);

    fclose(arqConfig);
    arqConfig = NULL;

    
    return 0;
}

/* unicamente, por: SANT! */
