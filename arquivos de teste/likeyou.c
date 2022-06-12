#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
    char oi[10] = "oi";
    char fala[20];

    strncpy(fala, &oi[0], 2);
    fala[2] = '\0';

    printf("%s", fala);
    return 0;
}
