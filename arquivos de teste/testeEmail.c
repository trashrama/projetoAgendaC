#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define TAMMAX_EMAIL 50
#define TAMMAX_AGENDA 3

struct st_pessoa{
    char email[TAMMAX_EMAIL];
};

struct st_agenda{
    struct st_pessoa contato[TAMMAX_AGENDA];
}agenda, aux;


char registroEmail(int total){
    int temArroba = FALSE;
    int tamanhoEmail;

    char email[TAMMAX_EMAIL];

    while(temArroba == FALSE){
        printf("Digite seu e-mail: ");
        fgets(email, TAMMAX_EMAIL-1, stdin);
        email[strcspn(email, "\n")] = 0;
        tamanhoEmail = strlen(email);
        

        for (int i = 0; i <= tamanhoEmail; i++){
            if (email[i] == '@'){
                if ( (email[i+1] != '\0') && (i != 0) ){
                    temArroba = TRUE;
                    strcpy(agenda.contato[total].email, email);
                    return 0;
                }
            }
        }
        /* 
            A função realiza as seguintes ações:
            Percorre todos os caracteres do e-mail, buscando um '@'
            Caso ache, realiza outra verificação: Se o @ é o úlitmo caracter (que não deve ser)
            E se o @ é o primeiro caracter.

            Obedecendo assim, a lei <nome>@<domínio>.

            Caso todas as condições forem verdade, ele copia a variável temporária 'email'
            para o atributo email da struct contato, e finaliza a função com o return 0.

            Caso contrário, ele entrará loop até as condições serem verdade.
        */
        printf("E-mail inválido!\n");
    }

}

int main(int argc, char const *argv[]){
    
    int total = 0;
    char email[TAMMAX_EMAIL];

    verificarEmail(total);

    printf("%s", agenda.contato[total].email);
    


    return 0;
}
