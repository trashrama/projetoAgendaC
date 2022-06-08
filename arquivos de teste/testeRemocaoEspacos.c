#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

void tirarEspacos(char *nome){
    //tira o primeiro espaço e arruma as posições
    int TAM_NOME = strlen(nome);
    char stringSem[TAM_NOME];
    
    int contadorEspacos, j;
    for (int i = 0; i < strlen(nome); i++){
        if(nome[i] != ' '){
            contadorEspacos = 0;
            stringSem[j] = nome[i];
            j++;
            printf("%s\n", stringSem);
        }else{
            contadorEspacos++;
            if (contadorEspacos == 1){
            stringSem[j] = ' ';
            j++;

            }
        }
    }

    for (int i = j; i < TAM_NOME-1; i++){
        stringSem[i] = '\0';
    } 
    
    
    printf("%s", stringSem);
	
}
   
    


int main(int argc, char const *argv[]){

    setlocale(LC_ALL,"");
    char nome[] = {"Roberto de Almeida Façanha"};

    tirarEspacos(nome);
  //  printf("%s", nome);

    //1 e 32 da manha essa e foda viado neyma neyma neyma neyma piquezin dos cria
    
    
    
    return 0;
}

