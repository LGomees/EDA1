#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa {
    char *nome;
    char *telefone;
    char *endereco;
    unsigned int cep;
    char *dataDeNascimento;
    struct Pessoa *prox;
} Pessoa;

Pessoa *criaListaVazia();
Pessoa *insereInicio(Pessoa *l, char*, char*, char*, unsigned int, char*);
void libera(Pessoa *l);

int main () {

    return 0;
}

Pessoa *criaListaVazia() {
    return NULL;
}

Pessoa *insereInicio(Pessoa *l, char *nome, char *telefone, char *endereco, unsigned int cep, char *nascimento) {

    Pessoa *novo;
    novo = (Pessoa *) malloc(sizeof(Pessoa));
    if(novo == NULL) {
        printf("Erro na alocação!");
        exit(-1);
    }

    novo->nome = nome;
    novo->telefone = telefone;
    novo->endereco = endereco;
    novo->cep = cep;
    novo->dataDeNascimento = nascimento;

    if(l == NULL) {
        novo->prox = NULL;
        return novo;
    } else {
        novo->prox = l;
        return novo;
    }
}

void libera(Pessoa *l) {
    Pessoa *aux;

    for(aux = l; aux != NULL; l = aux) {
        aux = aux->prox;
        free(l);
    }
}