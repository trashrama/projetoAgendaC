#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMMAX_TEL 12


char* printarTel(char telefone[TAMMAX_TEL]){
    char ddd[4], pref[2], telpp[8], telsp[8];

    // A cadeia de caracteres 'telpp' refere-se aos quatro primeiros dígitos do número de telefone.
    // A cadeia de caracteres 'telsp' refere-se aos quatro últimos dígitos do número de telefone.
    

    strncpy(ddd,&telefone[0],2);
    strncpy(pref,&telefone[2],1);
    strncpy(telpp,&telefone[3],5);
    strncpy(telsp,&telefone[7],5);
    telsp[4] = telpp[4] = pref[1] = ddd[2] = '\0';

    char* telefoneFormatado = malloc(18);
    sprintf(telefoneFormatado, "(%s) %s. %s-%s", ddd, pref, telpp, telsp);
    
    return telefoneFormatado;
}

int main(int argc, char const *argv[]){
    
    char numero[] = "88999586090";

    printf("%s", printarTel(numero));


    return 0;
}
