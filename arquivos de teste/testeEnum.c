#include <stdio.h>
#include <stdlib.h>

#define TAMMAX_AGENDA 5

struct st_pessoa{
    enum tipoEndereco{Alameda=1, Avenida, Praça, Rua}tipoEndereco;
};

struct st_agenda{
    struct st_pessoa contato[TAMMAX_AGENDA];
}agenda, aux;

int main(int argc, char const *argv[]){

    scanf("%i", &agenda.contato[0].tipoEndereco);

    switch (agenda.contato[0].tipoEndereco){
    case Alameda:
        printf("Alameda");
        break;
    case Avenida:
        printf("Avenida");
        break;
    case Praça:
        printf("Praça");
        break;
    case Rua:
        printf("Rua");
        break;
    default:
        break;
    }

    return 0;
}

