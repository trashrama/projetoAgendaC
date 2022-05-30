#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char const *argv[]){

    char opcao;
    printf("Deseja adicionar uma nota? (S/N): ");
    lerOpcao(&opcao);
    printf("opcao:%c", opcao);
    

    return 0;
}
