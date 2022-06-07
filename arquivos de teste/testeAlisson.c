#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TAM_NOME 100

   typedef struct agenda
 {
     char nome_contato [ TAM_NOME ];
     char endereco [300];
     char tipo_endereco;
     int numero_endereco;
     int telefone [ 11 ];
     int tipo_telefone;
     char email [ 200 ];
     char rede_social[100];
     char tipo_de_rede;
 } contato ;


void adicionarContatos( contato usuario[100], int *i)
{
    setlocale(LC_ALL,"");
    printf(" ... ADICIONANDO CONTATO.\n");
    
    printf(" - NOME DO CONTATO: ");
    fflush(stdin);
    scanf("%[^\n]s", &usuario[*i].nome_contato);

    printf(" - ENDEREÇO: ");
    fflush(stdin);
    scanf("%[^\n]s", &usuario[*i].endereco);

    printf(" - NUMERO ENDEREÇO: ");
    scanf("%i", &usuario[*i].telefone);

    printf(" - E-MAIL: ");
    fflush(stdin);
    scanf("%[^\n]s", &usuario[*i].email);

    printf(" - REDE SOCIAL: ");
    scanf("%[^\n]s", &usuario[*i].rede_social);

    (*i)++;


}


void listarContatos( contato usuario[100], int *i)
{
    for (int j = 0; j < *i; j++){
        printf("- NOME DO CONTATO: %s \n", usuario[j].nome_contato); 
        printf(" - ENDEREÇO: %s \n ", usuario[j].endereco);
        printf("- TELEFONE: %i \n", usuario[j].telefone);
        printf(" - E-MAIL DO CONTATO: %s \n", usuario[j].email);
        printf(" - REDE SOCIAL: %s", usuario[j].rede_social);   
        }
    
}

void alterarContatos(contato usuario)
{
     setlocale(LC_ALL,"");
     printf("Função não implementada. \n");
}

void excluirContatos(contato usuario)
{
     setlocale(LC_ALL,"");
     printf("Função não implementada. \n");
}


int main( ){
 
    setlocale(LC_ALL,"");


        // Criação do Arquivo e abertura do arquivo
        FILE *ptrArquivo = NULL;
        ptrArquivo = fopen ("DADOS-DO-REGISTRO.txt", "w");


        int opcao, total;
        total = 0;
        contato usuario[100];


 // laço para o Usuário decidir o que o codigo ira executar
do{

        printf("------------------------------------------\n");
        printf("- 1. Listar Contatos:                    -\n");
        printf("- 2. Adicionar Contato:                  -\n");
        printf("- 3. Alterar Contato:                    -\n");
        printf("- 4. Excluir Contato:                    -\n");
        printf("- 0. Sair:                               -\n");
        printf("------------------------------------------\n");

        scanf("%i", &opcao);

    switch (opcao)
    {

    case 1:
        listarContatos(usuario, &total);
        break;

    case 2:
        adicionarContatos(usuario, &total);
        break;

    case 3:
        alterarContatos(usuario[total]);
        break;

    case 4:
        excluirContatos(usuario[total]);
        break;

    case 0:
        printf("------------------------------------------\n");
        printf("-SAINDO ,_,                              -\n");
        printf("------------------------------------------\n");
        break;

    default:
        printf("------------------------------------------\n");
        printf("- Essa Opção não Existe.                 -\n");
        printf("------------------------------------------\n");
        break;

    }


}while(opcao != 0);

    return 0;

}


//Autor TeusVieira&Alioh