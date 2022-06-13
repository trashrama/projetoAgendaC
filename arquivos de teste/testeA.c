 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 200
#define TAM_VET 10

enum tipoEndereco { Alameda, Avenida, Praca, Rua, Travessa };
enum tipoContato { Celular, Fixo, Comercial, Pessoal, Fax };
enum tipoSocial { Instagram, Facebook, LinkedIn, outro };


typedef struct {
    char nome [ TAM_NOME ];
    char telefone [ TAM_NOME ];
    char redeSocial [ TAM_NOME ];
    char endereco [ TAM_NOME ];
    char email [ TAM_NOME ];
    char tipoContato [ TAM_NOME ];
    int numeroCasa, id;
    enum tipoEndereco tpEnd;
    enum tipoContato tpCon;
    enum tipoSocial tpSoci;
} registro;


char *obterNomeTelefone ( int tpCon )
{
    const char *nomeTelefone[] =
    {
        "Cel.", "Fix.", "Com.", "Pes.", "Fax."
    };

    return ( nomeTelefone [ tpCon ] );
}


int main(int argc, char const *argv[])
{

    registro pessoa [ TAM_VET ];

    int qtdPessoa = 0;
    //FUNÇÂO QUE ESPECIFICA O TIPO DE TELEFONE
        printf ( "\nSelecione o tipo de telefone\n" );
        printf ( "1 - Celular\n" );
        printf ( "2 - Fixo\n" );
        printf ( "3 - Comercial\n" );
        printf ( "4 - Pessoal\n" );
        printf ( "5 - Fax\n" );
        scanf ( "%i", &pessoa[qtdPessoa].tpCon );

        printf("%s", obterNomeTelefone(pessoa[qtdPessoa].tpCon-1) );

    return 0;
}

 
 
  
