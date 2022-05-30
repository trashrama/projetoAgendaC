#include <stdio.h>
#include <string.h>
#include <locale.h>

#define TAM_AGENDA 10



//scanf ("%[^\n]s", nomevariavel);aceita todos os caracteres menos o enter
//scanf ("%100[^\n]s", nomevariavel); idem anterior limitado a 100 caracteres
//scanf ("%[0123456789]s", nomevariavel); aceita algarismos romanos
typedef struct endereço {
    char rua [100];
    int numero;
    char bairro[50];
    char cidade [50];
    int cep;

};
 typedef struct CriarContato{
   char nome [100];
   int telefone [100];
   char email [100];
   char redes_sociais [20];
   struct endereço endereco[TAM_AGENDA];
   enum tipo_contato{celular, comercial, fixo, pessoal, fax, personalizado}tpcontato;
   enum tipo_endereco {Alameda, Avenida, Praça, Rua, Travessa}tpendereco;
   enum tipo_redes_sociais{Instagram, Facebook, LinkedIn, outros}tpredessociais;

};

int main (){
  struct CriarContato Pessoa;
  struct endereço Dados;


printf ("\t Criar contato:/n");
printf ("\t Digite o tipo de contato:\n");
scanf("%d", &Pessoa[].tpcontato);
   if((tpcontato >= celular) && (tpcontato <= personalizado)){
       //switch imprime na tela o valor referente a cada campo
       switch (tpcontato){
           case celular:
           printf("%d - celular",tpcontato);
           break;
            case comercial:
           printf("%d - comercial",tpcontato);
           break;
            case fixo:
           printf("%d - fixo",tpcontato);
           break;
            case pessoal:
           printf("%d - pessoal",tpcontato);
           break;
            case fax:
           printf("%d - fax",tpcontato);
           break;
            case personalizado:
           printf("%d - personalizado",tpcontato);
           break;
       }
   }

printf ("/t Nome:/n");
scanf("%[^\n]s",Pessoa.nome);
 printf ("/t Telefone:/n");
  scanf("%[^\n]s",Pessoa.telefone);
  printf ("/t endereço:/n");
   printf ("/t rua:/n");
    scanf("%[^\n]s",Dados.rua);
     printf ("/t Número da casa:/n");
      scanf("%[^\n]s",Dados.numero);
       printf ("/t Bairro:/n");
        scanf("%[^\n]s",Dados.bairro);
         printf ("/t Cidade:/n");
          scanf("%[^\n]s",Dados.cidade);
           printf ("/t CEP:/n");
            scanf("%[^\n]s",Dados.cep);
 return 0;           
}



#define LIMITECONTT 250

struct contato contatos[LIMITECONTT];
int contador = 0;


void criarContato(){
     printf("\nCriar contato:\n");
}
void listarContatos(){
     printf("\nListar contatos:\n");
}

void buscarContatos(){
     printf("\tBuscar contatos:\n");
}
void EditarContato(){
     printf("\t Editar contato:\n");
}
void excluirContato (){
     printf("\t Excluir contato:\n");
}
void sairDaLista(){
     printf("\n Sair da lista:\n");
}


void menuDefault(){

    int opcao = 0;

    while(opcao != 9){
        printf("Selecione a opção desejada:\n");
        printf("1 - Novo contato:\n");
        printf("2 - Lista de contatos:\n");
        printf("3 - Buscar contatos.\n");
        printf("4 - Editar contato. \n");
        printf("5 - excluir contato. \n");
        printf("9 - Sair.\n");

        scanf("%i",&opcao);
        fflush(stdin);

        if(opcao != 9){
            switch(opcao){
                //cria novo contato
                case 1: criarContato();
                break;
                // mostra a lista de contatos
                case 2: listarContatos();
                break;
                //busca contatos
                case 3: buscarContatos();
                break;
                // edita o contato que o usuario pede
                case 4: EditarContato();
                break;
                //exclui contato
                case 5: excluirContato();
                break;
                //sai da lista
                case 6: sairDaLista();
                break;
                default: printf("Opcao invalida.");
            }
        }else{
            printf("Ate breve!\n");
        }
    }
}
