#include <stdio.h>
#include <stdlib.h>

typedef struct ponto{
    char nome;
    struct ponto * proximo;
}t_ponto;

int main(){

    char *fim = "FIM";
    int cont = 0;

    t_ponto * ini_ponto;
    t_ponto * proximo_ponto;

    ini_ponto = (t_ponto *)malloc(sizeof(t_ponto));
    if(ini_ponto == NULL)
        exit(1);
    proximo_ponto = ini_ponto;

    while(1){
        printf("Digite nomes: ");
        scanf("%s", &proximo_ponto->nome);
        if(proximo_ponto->nome != *fim){
            proximo_ponto->proximo = (t_ponto *)malloc(sizeof(t_ponto));
            proximo_ponto = proximo_ponto->proximo;
        }else{
            break;
        }
    }
    printf("\n");
    
    proximo_ponto->proximo = NULL;
    proximo_ponto = ini_ponto;

    printf("Nomes digitados:\n");
    while(proximo_ponto != NULL){
        cont = cont + 1;
        proximo_ponto = proximo_ponto->proximo;
    }
    int i, j = 0;
    i = cont - 1;
    j = i;
    proximo_ponto = ini_ponto;

    for(; i > 0; i--){
      for(; j > 0; j--){
        if(j == 1){
        printf("%s\n", &proximo_ponto->nome);
        }
        proximo_ponto = proximo_ponto->proximo;
      }
    j = i - 1;
    proximo_ponto = ini_ponto;  
    }
    free(proximo_ponto->proximo);
    free(ini_ponto);
}
