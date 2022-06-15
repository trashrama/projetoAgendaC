#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define TAMMAX_BUFFER 128
#define TAMMAX_LINHA_ARQ 500
#define TAMMAX_DEST 30

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
void lerFormatStr(char *var, int tamanho, int tamanhoEhFixo){
    
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


// FUNÇÕES DE CONFIGURAÇÃO
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
void lerConfiguracoes(char* locacao_dados, int* auto_save, int* modo_cores,  int* TAMMAX_CONTATOS){

    FILE *arqConfig = NULL;
    char linha[TAMMAX_LINHA_ARQ];
    char bufferAtoi[2];

    int numLinha = 0;
    int comecoDados, fimDados;

    arqConfig = fopen ("config.ini", "r");
    
    if (arqConfig == NULL){
        arqConfig = fopen ("config.ini", "w");
        // estrutura padrao de configuração
        fprintf(arqConfig, "arquivo_dados=\"dados.csv\"\n");
        fprintf(arqConfig, "auto_save=%i\n", TRUE);
        fprintf(arqConfig, "modo_cores=%i\n", FALSE);
        fprintf(arqConfig, "num_max_contatos=%i\n", 5);

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

            *TAMMAX_CONTATOS = atoi(bufferAtoi);
            strcpy(bufferAtoi, "");

            break;
        }
        numLinha++;
    }

    fclose(arqConfig);
    arqConfig = NULL;

}
void editarConfiguracoes(char* locacao_dados, int* auto_save, int* modo_cores,  int* TAMMAX_CONTATOS){
    char opcao[2];
    char novoNomeArq[TAMMAX_DEST];
    int selecao;
     int novoTamanho;

    while(opcao[0] != 'N'){

        printf("*****[CONFIGURAÇÕES]*****\n");
        printf("Destino dos Dados = \"%s\"\n", locacao_dados);
        printf("Auto-Save = %s\n", printarEstado(*auto_save));
        printf("Modo Cores = %s\n", printarEstado(*modo_cores));
        printf("Número Máximo de Contatos = %i\n", *TAMMAX_CONTATOS);
        printf("Deseja editar alguma configuração? (S/N): ");
        lerOpcao(&opcao);
        
        if (opcao[0] != 'N'){

            printf("\n-------------------------------\n");
            printf("[1] Destino dos Dados = \"%s\"\n", locacao_dados);
            printf("[2] Auto-Save = %s\n", printarEstado(*auto_save));
            printf("[3] Modo Cores = %s\n", printarEstado(*modo_cores));
            printf("[4] Número Máximo de Contatos = %i\n", *TAMMAX_CONTATOS);
            printf("Qual opção deseja selecionar?: ");
            selecao = lerSelecao(4);

            switch (selecao){
            case 1:
                printf("Digite a novo nome do arquivo: ");
                lerFormatStr(novoNomeArq, TAMMAX_DEST-3, FALSE);
                tratarNomeArquivo(novoNomeArq);
                printf("Confirma o novo nome do arquivo? (S/N): ");
                strcpy(opcao, "");
                lerOpcao(&opcao);
                if(opcao[0] == 'S'){
                    printf("Modificação efetuada.\n");
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
                printf("Modificação efetuada.\n\n");
                break;
            case 4:
                printf("Digite o novo valor máximo de contatos: ");
                novoTamanho = lerNum();
                printf("Confirma o novo valor máximo de contatos? (S/N): ");
                strcpy(opcao, "");
                lerOpcao(&opcao);

                if(opcao[0] == 'S'){
                    printf("Modificação efetuada.\n\n");
                    *TAMMAX_CONTATOS = novoTamanho;
                }else{
                    printf("Edição cancelada.\n");
                }

                break;
            
            default:
                break;
            }
        }
    
    }

    gravarConfiguracoes(locacao_dados, &auto_save, &modo_cores, &TAMMAX_CONTATOS);


}
void gravarConfiguracoes(char* locacao_dados, int* auto_save, int* modo_cores,  int* TAMMAX_CONTATOS){
    FILE *arqConfig = NULL;

    arqConfig = fopen ("config.ini", "w");

    fprintf(arqConfig, "arquivo_dados=\"%s\"\n", locacao_dados);
    fprintf(arqConfig, "auto_save=%i\n", *auto_save);
    fprintf(arqConfig, "modo_cores=%i\n", *modo_cores);
    fprintf(arqConfig, "num_max_contatos=%i\n", *TAMMAX_CONTATOS);

    fclose(arqConfig);
    arqConfig = NULL;

    
    return 0;
}


int main(int argc, char const *argv[]){
    
    char locacao_dados[TAMMAX_DEST];
    int auto_save;
    int modo_cores;
    int TAMMAX_CONTATOS;
    

    lerConfiguracoes(locacao_dados, &auto_save, &modo_cores, &TAMMAX_CONTATOS);
    
    editarConfiguracoes(locacao_dados, &auto_save, &modo_cores, &TAMMAX_CONTATOS);

    return 0;
}


