#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa {
    char *nome;
    char *telefone;
    char *endereco;
    unsigned int cep;
    char *dataDeNascimento;
    struct pessoa *prox;
    struct pessoa *ant;
} Pessoa;

Pessoa *criaListaVazia();
Pessoa *insereInicio(Pessoa *l, char*, char*, char*, unsigned int, char*);
void libera(Pessoa *l);
void lerArquivo(FILE *f, Pessoa *contato);
void imprime(Pessoa *l);
Pessoa *removeContato(Pessoa *l, char*);
void visualizaNome(Pessoa *l, char*);


int main () {
    Pessoa *contatos;
    contatos = criaListaVazia();
    FILE *contatosFile = fopen("./contatos.txt", "r+");
    if (contatosFile == NULL) {
        printf("Falha na alocação do arquivo!\n");
        exit(1);
    }

    lerArquivo(contatosFile, contatos);
    //imprime(contatos);

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
    printf("Nome: %s\nTelefone: %s\nEndereco: %s\n", novo->nome, novo->telefone, novo->endereco);

    if(l == NULL) {
        novo->prox = NULL;
        novo->ant = NULL;
        return novo;
    } else {
        printf("DEPOIS - Nome: %s\nTelefone: %s\nEndereco: %s\n", l->nome, l->telefone, l->endereco);
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
    char cepStr[12] = "";
    char nome[100] = "";
    char aux[100] = "";
    char telefone[12] = "";
    char endereco[100] = "";
    unsigned int cep;
    char dataDeNascimento[12] = "";
    do {
        if(cont == 0) {
            fgets(nome, 100, file);
            //printf("Nome: %s", nome);
            cont++;
        } else if (cont == 1) {
            fgets(telefone, 12, file);
            cont++;
            //printf("Telefone: %s", telefone);
        } else if (cont == 2) {
            fgets(endereco, 100, file);
            cont++;
            //printf("Endereco: %s", endereco);
        } else if (cont == 3) {
            fgets(cepStr, 12, file);
            cep = atoi(cepStr);
            cont++;
            //printf("CEP: %d\n", cep);
        } else if (cont == 4) {
            fgets(dataDeNascimento, 12, file);
            cont++;
            //printf("Data de Nascimento: %s", dataDeNascimento);
        } else if (cont == 5) {
            fgets(aux, 100, file);
            contato = insereInicio(contato, nome, telefone, endereco, cep, dataDeNascimento);
            cont = 0;
            //imprime(contato);
            *nome = '\0';
        }
    } while(!feof(file));

}

void imprime(Pessoa *l){
    Pessoa *aux;
    int i = 0;

    for(aux = l; aux != NULL; aux = aux->prox) {
        printf("%d ---------------------------- %p\n", i, aux);
        printf("Nome: %s\n", aux->nome);
        printf("Telefone: %s\n", aux->telefone);
        printf("Endereco: %s\n", aux->endereco);
        printf("CEP: %d\n", aux->cep);
        printf("Data de nascimento: %s\n", aux->dataDeNascimento);
        i++;
    }

}

Pessoa *removeContato(Pessoa *l, char* nome) {
    Pessoa *atual;
    Pessoa *anterior;
    Pessoa *posterior;

    for(atual = l; atual != NULL; atual = atual->prox) {
        if (nome == atual->nome) {
            anterior = atual->ant;
            posterior = atual->prox;
            anterior->prox = atual->prox;
            posterior->ant = atual->ant;
            free(atual);
        }
    }
}

void visualizaNome(Pessoa *l, char* nome) {
    Pessoa *atual;
    for(atual = l; atual != NULL; atual = atual->prox) {
        if (nome == atual->nome) {
            printf("-------------------------------\n");
            printf("Nome: %s", atual->nome);
            printf("Telefone: %s", atual->telefone);
            printf("Endereco: %s", atual->endereco);
            printf("CEP: %d\n", atual->cep);
            printf("Data de nascimento: %s\n", atual->dataDeNascimento);
        }
    }
}