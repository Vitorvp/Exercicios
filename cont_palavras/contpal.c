#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ler_arquivo(void *m);

typedef struct{
  char *nome;
} paramentros_t;


int main(int argc, char *argv[]){

for (int i = 1; i < argc; i++){
    pthread_t t[i];
    paramentros_t p;

    p.nome = argv[i];

        pthread_create(&t[i], NULL, ler_arquivo, &p);
        pthread_join(t[i], NULL);
}

exit(EXIT_SUCCESS);

}

void *ler_arquivo(void*m){
    paramentros_t p = *((paramentros_t *) m);

    FILE *arq;
    char letra;
    int cont_palavras = 0, fim_texto = 0, linha = 0;
    int valido = 1;

    arq = fopen(p.nome, "r");

    while (!feof(arq))
 	{
  		fscanf(arq,"%c", &letra);
        if (letra != ' '){
            valido = 0;
        }
        
        if (letra == ' ' && valido == 0){
            cont_palavras++;
            valido = 1;
        }

        if (letra == 0){
            fim_texto = 0;
        }else if(letra != '\n' && letra != ' '){
            fim_texto = 1;
        }else if (letra == ' '){
            fim_texto = 0;
        }

        if(letra == '\n'){
            linha++;
        }
  	}

        printf("%s = %d palavra(s)\n",p.nome, (cont_palavras + fim_texto + (linha - 2)));

    return NULL;
}
