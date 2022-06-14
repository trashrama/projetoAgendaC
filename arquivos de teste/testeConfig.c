#include <stdio.h>
#include <stdlib.h>

#define TAMMAX_LINHA_ARQ 500
#define TRUE 1
#define FALSE 0

int lerConfiguracoes(){

    FILE *arqConfig = NULL;
    char linha[TAMMAX_LINHA_ARQ];
    int numLinha = 0;

    arqConfig = fopen ("config.ini", "r");
    
    if (arqConfig == NULL){
        arqConfig = fopen ("config.ini", "w");
        // estrutura padrao de configuração
        fprintf(arqConfig, "arquivo_dados=%i\n", FALSE);
        fprintf(arqConfig, "auto_save=%i\n", FALSE);
        fprintf(arqConfig, "modo_cores=%i\n", FALSE);
        fprintf(arqConfig, "num_max_contatos=%i\n", 5);

    }


    while( (fgets(linha, sizeof(linha), arqConfig)) != NULL){
        for (int i = 0; i < strlen(linha); i++){
            if(linha[i] == '='){

                
            }
        }
        
        
    }


    fclose(arqConfig);
    arqConfig = NULL;

    return 0;
}




int main(int argc, char const *argv[]){

    lerConfiguracoes();
    return 0;
}


