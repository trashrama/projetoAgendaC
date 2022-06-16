#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

//NUMOPCOES_END é uma pseuconstante para o número de opções enumeradas do endereço.
#define NUMOPCOES_END 5
//NUMOPCOES_CTT é uma pseuconstante para o número de opções enumeradas do contato.
#define NUMOPCOES_CTT 6
//NUMOPCOES_RS é uma pseuconstante para o número de opções enumeradas das redes sociais.
#define NUMOPCOES_RS 5

//TAMMAX_AGENDA é uma pseucostante para número máximo de contatos na agenda.
#define TAMMAX_AGENDA 5
#define TAMMAX_NOME 50
#define TAMMAX_ENDERECO 50
#define TAMMAX_TEL 12
#define TAMMAX_EMAIL 50
//TAMMAX_RS é uma pseucostante para o nome de usuário rede social.
#define TAMMAX_RS 20
#define TAMMAX_CEP 9
#define TAMMAX_NOTA 200

int main(int argc, char const *argv[])
{
    char subStrNome [ 16 ];
    char subStrEnd  [ 21 ];
    char subStrBairro [ 11 ];
    for ( int i = 0; i < nContatos; i++ )
    {
        strncpy ( subStrNome , contatos[i].nome, 15 );

        sprintf ( subStrEnd, "%s %s, %i",
            obterNomeEndereco ( contatos[i].tpEnd),
            contatos[i].endereco, contatos[i].numero );

        strncpy ( subStrBairro, contatos[i].bairro, 10 );
        printf ( "%-15s | %-20s | %-10s | %15s\n",
            subStrNome, subStrEnd,
            subStrBairro, contatos[i].email );
    }
    return 0;
}
