#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMMAX_BUFFER 128

int main(int argc, char const *argv[]){
    char buffer[TAMMAX_BUFFER];
    fgets(buffer, TAMMAX_BUFFER, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    printf("%s", buffer);
    return 0;
}
