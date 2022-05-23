#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    
    //fopen()
    
    //fprintf()
    //fread()
    //fwrite()
    //fgets()
    //fputchar()
    //fseek()
    //feof()

    //fclose()

//modos de abertura: R (read), W (write) & A (append)


// 0. declarar variável FILE*;
// 1. abrir arquivo;
// 2. verificar se a abertura do arquivo foi bem sucedida;
// 3. realizar operações de ENTRADA E SAÍDA;
// 4. fechar arquivo.

    char msg[30], nomeArq[30];
    FILE* arq = NULL;

    arq = fopen("gone.txt", "a");

    while (msg[0] != '\0'){
        printf("Digite alguma coisa do teclado (0 para parar): ");
        fgets(msg, 29, stdin);
        if(msg[0] != '0'){
            fprintf(arq, "%s", msg);
        }
    }
    
    
    fclose(arq);
    arq = NULL;
    
    return 0;
}
