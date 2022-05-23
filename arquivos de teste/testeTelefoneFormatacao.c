#include <stdio.h>
#include <stdlib.h>


#define TAMMAX_AGENDA 5
#define TAMMAX_TELSEMFORMAT 13
#define TAMMAX_TELEFONE 17
/* 

TAMMAX_TELSEMFORMAT é uma pseucostante para número máximo de caracteres de um telefone (sem formatação).
TAMMAX_TELEFONE é uma pseucostante para número máximo de caracteres de um telefone (já formatado).

 */

struct st_pessoa{
    char telefone[TAMMAX_TELEFONE];
    int ehFixo;
};

struct st_agenda{
    struct st_pessoa contato[TAMMAX_AGENDA];
}agenda, aux;



void formatarTel(char telefone[]){
    char ddd[4];
    char telpp[8];
    char telsp[8];
    char pref[3];

    ddd[0] = telefone[0];
    ddd[1] = telefone[1];

    pref[0] = telefone[2];

    telpp[0] = telefone[3];
    telpp[1] = telefone[4];
    telpp[2] = telefone[5];
    telpp[3] = telefone[6];

    printf("(%s) %s %s\n ", ddd, pref, telpp);

    
}


int main(int argc, char const *argv[]){
    
    char telefoneSemFormat[TAMMAX_TELSEMFORMAT];

    fgets(telefoneSemFormat, TAMMAX_TELSEMFORMAT-1, stdin);
    telefoneSemFormat[strcspn(telefoneSemFormat, "\n")] = 0;

    formatarTel(telefoneSemFormat);
    
    return 0;
}

