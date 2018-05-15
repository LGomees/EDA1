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
    char cepStr[10] = "";
    char nome[100] = "";
    char telefone[10] = "";
    char endereco[100] = "";
    unsigned int cep;
    char dataDeNascimento[10] = "";
    do {
        printf("cont: %d, x: %c\n", cont, x);
        fscanf(file, "%c", &x);
        if(cont == 0 && x != '\n') {
            strcat(nome, &x);
            printf("nome: %s\n", nome);
        } else if (cont == 1 && x != '\n') {
            strcat(telefone, &x);
            printf("telefone: %s\n", telefone);
        } else if (cont == 2 && x != '\n') {
            strcat(endereco, &x);
            printf("endereco: %s\n", endereco);
        } else if (cont == 3 && x != '\n') {
            strcat(cepStr, &x);
            cep = atoi(cepStr);
            printf("cep: %d\n", cep);
        } else if (cont == 4 && x != '\n') {
            strcat(dataDeNascimento, &x);
            contData++;
            if(contData == 2 || contData == 4) {
                strcat(dataDeNascimento, "/");
            }
            printf("data: %s\n", dataDeNascimento);
        }
        if(x == '\n'){
            cont++;
        } else if (x == '$') {
            contato->nome = (char*) malloc(sizeof(char)*100);
            contato->telefone = (char*) malloc(sizeof(char)*10);
            contato->endereco = (char*) malloc(sizeof(char)*100);
            contato->dataDeNascimento = (char*) malloc(sizeof(char)*10);
            printf("5\n");
            contato = insereInicio(contato, nome, telefone, endereco, cep, dataDeNascimento);
            cont = -1;
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