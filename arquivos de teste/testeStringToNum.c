#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int stringParaNumero(){
    //a variável tamanho se refere ao tamanho da string (no caso, números, no máximo, 5 caracteres.)
    char var[50], buffer[6];
    int num = 0;
    int ehPalavra, teste;

    while (num == 0){
        fgets(var, 50, stdin); 
        ehPalavra = FALSE;

        for (int i = 0; i < strlen(var); i++){
            if(isalpha(var[i]) != 0){
                ehPalavra = TRUE;
            }
        }

        if(ehPalavra == FALSE){
            //testa se o atoi consegue transformar em número;
            teste = atoi(var);
            if (teste == 0){
                printf("Inválido\nDigite um número: ");
                getchar();
            }else{
                //Corta o número se for muito grande. (Teoricamente) Não existem casas com mais de cinco digitos.
                strncpy(buffer, var, 5);
                buffer[5] = '\0'; 
                num = atoi(buffer);
            }
        }else{
            printf("Você está digitando uma palavra\nDigite um número: ");
        }
         
        
    }
    return num;
}

int main(int argc, char const *argv[]){
    
    int num;
    num = stringParaNumero();
    printf("%i", num);

    return 0;
}
