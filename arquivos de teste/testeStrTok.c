#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    
    char nome[] = {"carlos santiago do nascimento ferreira"};
    char *pt;

    pt = strtok(nome, " ");
    while(pt){
        printf("%s\n", pt);
        pt = strtok(NULL, " ");
    }

    printf("%s", pt);


    return 0;
}
