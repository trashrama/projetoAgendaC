#include <stdio.h>
#include <stdlib.h>


struct st_pessoa{
    enum tipoEndereco{Alameda=1, Avenida, Praca, Rua, Travessa, Rodovia}tipoEndereco;
    enum tipoContato{Celular=1, Comercial, Fixo, Pessoal, Fax, Personalizado}tipoContato;
    enum tipoRedeSocial{Twitter=1, Facebook, Instagram, GitHub, LinkedIn}tipoRedeSocial;
    int numCasa;
};

struct st_agenda{
    struct st_pessoa contato[12];
}agenda, aux;



int main(int argc, char const *argv[]){
    scanf("%i", &agenda.contato[0].tipoEndereco);
    printf("%s", printarEnumerados(2, agenda.contato[0].tipoEndereco));

    return 0;
}
