#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

void tirarEspacos(char *nome){
    //tira o primeiro espaço e arruma as posições
    int i, j;
    int TAM_NOME = strlen(nome);
    char stringSem[TAM_NOME];
    char *token;


    //procurar espaços no meio
    strcpy(stringSem, "");
    strcpy(stringSem, nome);
    strcpy(nome, "");

    token = strtok(stringSem, " ");
    while (token != NULL){
        strcat(nome, token);
        strcat(nome, " ");
        token = strtok(NULL, " ");
    }

    //procurar espaços no começo
    for (i = 0; i < TAM_NOME; i++){
        if (nome[i] != ' '){
            break;
        }
    }

    //calular o novo tamanho sem os espaços do nome original
    TAM_NOME = strlen(nome) - i;

    //procurar espaços no final
    for (j = TAM_NOME; j > 0; j--){
        if (nome[j] != ' '){
            break;
        }
    }

    strcpy(stringSem, nome);

    strncpy(nome, &stringSem[i], j-1);
    nome[j-1] = '\0';
    
} 
void deixarMinusculo(char *nome){
    int TAM_NOME = strlen(nome);
    for (int i = 0; i < TAM_NOME; i++){
        nome[i] = tolower(nome[i]);
    }
}
void capitalizarNome(char *nome){
    int TAM_NOME = strlen(nome);
    int primeiraPos, contador, jaTevePreposicao;

    jaTevePreposicao = FALSE;
    primeiraPos = contador = 0;

    //capitalizando o primeiro caracter;
    nome[0] = toupper(nome[0]);

      /*
        Criei uma variável contador que conta o tamanho da string e uma que pega a primeira posição após o espaço.
        Para nomes como "Ari de Sá", criei uma variável que conta quando existem preposições
        se já tiver uma preposição, a próxima palavra com dois caracteres será capitalizada.
        A preposição no meio do nome não será printada, já que printamos somente o nome e sobrenome,
        mas em caso de printar nome e sobrenome em outra função, já temos um uso aqui.
    */

    //capitalizando sobrenome sem preposição
    for (int i = 0; i < TAM_NOME; i++){
        
        if (nome[i] == ' '){
            primeiraPos = i+1;
            nome[primeiraPos] = toupper(nome[primeiraPos]);
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
    int temEspaco = verificarEspacos(nome);
    char primeiroNome[20], ultimoSobrenome[20];
    char* nomeResumido = malloc(40);

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
        //strncpy copia uma quantidade N de caracteres, lembrar disso
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


int main(int argc, char const *argv[]){

    char nome[] = {"buceto"};

    //printf("%s", nome);
    tirarEspacos(nome);
    deixarMinusculo(nome);
    capitalizarNome(nome);
    //printf("%s", nome);

    printf("%s", printarNome(nome));
    
    
    
    return 0;
}

