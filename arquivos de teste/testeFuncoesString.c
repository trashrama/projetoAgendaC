#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

void tirarEspacos(char *nome){
    //tira o primeiro espaço e arruma as posições
    int TAM_NOME = strlen(nome);
    if (nome[0] == ' '){
        for (int i = 0; i < TAM_NOME; i++){
            nome[i] = nome[i+1];
        } 
    }
    
    //oq estou tentando fazer é uma funçao pra tirar o espaço de um ultimo caracter
    if (nome[TAM_NOME-1] == ' '){
        nome[TAM_NOME-1] = '\0';
    }
    
    //verificar se tem dois espaços
    for (int i = 0; i < TAM_NOME; i++){
        if ( (nome[i] == ' ') && (nome[i+1] == ' ') ){
            for (int j = i; j < TAM_NOME; j++){
                nome[j] = nome[j+1];
            }
        }  
    }

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

    for (int i = 0; i < TAM_NOME; i++){
    
  
        /*
        Criei uma variável contador e uma que pega a primeira posição após o espaço.
        Para nomes como "Ari de Sá", criei uma variável que conta quando existem preposições
        se já tiver uma preposição, a próxima palavra com dois caracteres será capitalizada.
        */

        if (nome[i] == ' '){
            contador = 0;
            primeiraPos = i+1;
        }

        if ( (contador >= 4) || (contador == 2 && jaTevePreposicao == TRUE) ) {
            nome[primeiraPos] = toupper(nome[primeiraPos]);

            if (jaTevePreposicao == TRUE){
                jaTevePreposicao = FALSE;
            }
        }

        if ((contador == 2) && (nome[i+1] == ' ')){
            jaTevePreposicao = TRUE;
        } 

        contador++;
        
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
void printarNome(int temEspaco, char *nome){
    char primeiroNome[20], ultimoSobrenome[20];
    int TAM_NOME = strlen(nome);

    if (temEspaco == TRUE){
        int finalPrNome = 0;
        for (int i = 0; i < TAM_NOME; i++){
            if (nome[i] == ' '){
                finalPrNome = i-1;
                // esse -1 e mais +1 na funçao seguinte eh pq
                // fiz i-1 pra pegar a posiçao anterior ao espaço
                strncpy(primeiroNome, &nome[0], finalPrNome+1);
                // e adicionei 1 pois a funçao strncpy usa o ultimo caracter de delimitador
                break;
            }
        }

        
        // pegar ultimo sobrenome
        int comecoSobrenome = 0;
        for (int i = TAM_NOME; i > 0; i--){
            if (nome[i] == ' '){
                comecoSobrenome = i+1;
                strncpy(ultimoSobrenome, &nome[comecoSobrenome], TAM_NOME-1);
                break;
            }
        }
            printf("%s %s\n", primeiroNome, ultimoSobrenome);

    }else{
        printf("%s", nome);
    }

}
int main(int argc, char const *argv[]){

    char nome[] = {" elto"};
    char primeiroNome[20];
    char ultimoSobrenome[20];
    int TAM_NOME = strlen(nome);


    tirarEspacos(nome);
    deixarMinusculo(nome);
    capitalizarNome(nome);
    verificarEspacos(nome);

    //1 e 32 da manha essa e foda viado neyma neyma neyma neyma piquezin dos cria
    int temEspaco = verificarEspacos;
    printarNome(temEspaco, nome);
    //pegar primeiro nome
    
    
    
    return 0;
}

