#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ordenarPorNome(char vetor[], int tam){

    int r;
    char aux[80];

    for (int i = 0; i < tam; i++){
        for (int j = i+1; j < tam; j++){
            r = strcmp(vetor[i], vetor[j]);
            if (r>0){
                strcpy(aux, vetor[i]);
                strcpy(vetor[i], vetor[j]);
                strcpy(vetor[j], aux);

            }
        }
        
    }

}


int main(int argc, char const *argv[]){
   

    char vetor[10][50];
    int tam = 3;
    printf("Digite %i nomes", tam);

    for (int i = 0; i < tam; i++){
        gets(vetor[i]);
    }
    
    ordenarPorNome(vetor, tam);
    

    
    
    return 0;
}
