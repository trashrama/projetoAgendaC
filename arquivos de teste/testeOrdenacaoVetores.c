#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ordenarVetor (char* vetor[], int total){
    char aux[80];
    printf("%i", total);
    int r;

    for (int i = 0; i <= total; i++){
       for (int j = i+1; j <= total; j++){
           r = strcmp(vetor[i], vetor[j]);
           if (r > 0){
            strcpy(aux, vetor[i]);
            strcpy(vetor[i], vetor[j]);
            strcpy(vetor[j], aux);
           }
           
       }
       
    }
    
    
}

int main(int argc, char const *argv[])
{
    char* nome[20] = {"sant", "alysson", "lucas", "alisson", "matheus", "luquinha", "luã"};
    int total = 7;
    ordenarVetor(nome, total);
    
    
    
    return 0;
}
