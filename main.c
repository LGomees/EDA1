#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void lerArquivo(FILE *f, Pessoa *contato);
void imprime(Pessoa *l);

int main () {
    Pessoa *contatos;
    contatos = criaListaVazia();
    FILE *contatosFile = fopen("./contatos.txt", "r+");
    if (contatosFile == NULL) {
        printf("Falha na alocação do arquivo!\n");
        exit(1);
    }

    lerArquivo(contatosFile, contatos);
    imprime(contatos);

    return 0;
}

Pessoa *criaListaVazia() {
    return NULL;
}

Pessoa *insereInicio(Pessoa *l, char *nome, char *telefone, char *endereco, unsigned int cep, char *nascimento) {

    Pessoa *novo;
    novo = (Pessoa *) malloc(sizeof(Pessoa));
    if(novo == NULL) {
        printf("Erro na alocação!\n");
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

void lerArquivo(FILE *file, Pessoa *contato) {
    char x;
    int cont = 0, contData = 0;
    char cepStr[11] = "";
    char nome[100] = "";
    char aux[100] = "";
    char telefone[11] = "";
    char endereco[100] = "";
    unsigned int cep;
    char dataDeNascimento[11] = "";
    do {
        printf("cont: %d, x: %c\n", cont, x);
        if(cont == 0) {
            fgets(nome, 100, file);
            printf("nome: %s\n", nome);
            cont++;
        } else if (cont == 1) {
            fgets(telefone, 11, file);
            printf("telefone: %s\n", telefone);
            cont++;
        } else if (cont == 2) {
            fgets(endereco, 100, file);
            printf("endereco: %s\n", endereco);
            cont++;
        } else if (cont == 3) {
            fgets(cepStr, 11, file);
            cep = atoi(cepStr);
            printf("cep: %d\n", cep);
            cont++;
        } else if (cont == 4) {
            fgets(dataDeNascimento, 11, file);
            printf("data: %s\n", dataDeNascimento);
            cont++;
        } else if (cont == 5) {
            fgets(nome, 100, file);
            contato->nome = (char*) malloc(sizeof(char)*100);
            contato->telefone = (char*) malloc(sizeof(char)*10);
            contato->endereco = (char*) malloc(sizeof(char)*100);
            contato->dataDeNascimento = (char*) malloc(sizeof(char)*10);
            contato = insereInicio(contato, nome, telefone, endereco, cep, dataDeNascimento);
            cont = 0;
            printf("6\n");
        }
    } while(!feof(file));

    imprime(contato);
}

void imprime(Pessoa *l){
    Pessoa *aux;
    int i = 0;

    for(aux = l; aux != NULL; aux = aux->prox) {
        printf("%d----------------------------\n", i);
        printf("Nome: %s\n", aux->nome);
        printf("Telefone: %s\n", aux->telefone);
        printf("Endereco: %s\n", aux->endereco);
        printf("CEP: %s\n", aux->cep);
        printf("Data de nascimento: %s\n", aux->dataDeNascimento);
        i++;
    }

}