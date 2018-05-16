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
void imprime(Pessoa *l);
Pessoa *removeContato(Pessoa *l, char*);
void visualizaNome(Pessoa *l, char*);
void reescreveArquivo(Pessoa *l);

int main () {
    Pessoa *contatos;
    contatos = criaListaVazia();
    FILE *contatosFile = fopen("./contatos.txt", "r+");
    if (contatosFile == NULL) {
        printf("Falha na alocação do arquivo!\n");
        exit(1);
    }

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
            fgets(nome, 100, contatosFile);
            cont++;
        } else if (cont == 1) {
            fgets(telefone, 15, contatosFile);
            cont++;
        } else if (cont == 2) {
            fgets(endereco, 100, contatosFile);
            cont++;
        } else if (cont == 3) {
            fgets(cepStr, 15, contatosFile);
            cep = atoi(cepStr);
            cont++;
        } else if (cont == 4) {
            fgets(dataDeNascimento, 15, contatosFile);
            cont++;
        } else if (cont == 5) {
            fgets(aux, 100, contatosFile);
            contatos = insereInicio(contatos, nome, telefone, endereco, cep, dataDeNascimento);
            cont = 0;
        }
    } while(!feof(contatosFile));

    //imprime(contatos);

    visualizaNome(contatos, "Toney Schaffner");

    reescreveArquivo(contatos);
    libera(contatos);

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

    novo->nome = (char*) malloc(sizeof(char)*100);
    novo->telefone = (char*) malloc(sizeof(char)*15);
    novo->endereco = (char*) malloc(sizeof(char)*100);
    novo->dataDeNascimento = (char*) malloc(sizeof(char)*15);

    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    strcpy(novo->endereco, endereco);
    novo->cep = cep;
    strcpy(novo->dataDeNascimento, nascimento);

    if(l == NULL) {
        novo->prox = NULL;
        //novo->ant = NULL;
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

void imprime(Pessoa *l){
    Pessoa *aux;
    int i = 0;

    for(aux = l; aux != NULL; aux = aux->prox) {
        printf("------------------------------\n");
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
        if (strncmp(atual->nome, nome, strlen(atual->nome)-2) == 0) {
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
        if (strncmp(atual->nome, nome, strlen(atual->nome)-2) == 0) {
            printf("-------------------------------\n");
            printf("Nome: %s", atual->nome);
            printf("Telefone: %s", atual->telefone);
            printf("Endereco: %s", atual->endereco);
            printf("CEP: %d\n", atual->cep);
            printf("Data de nascimento: %s\n", atual->dataDeNascimento);
        }
    }
}

void reescreveArquivo(Pessoa *l) {
    Pessoa *aux;
    FILE *contatosFile = fopen("./contatoss.txt", "w");
    if (contatosFile == NULL) {
        printf("Falha na alocação do arquivo!\n");
        exit(1);
    }

    for(aux = l; aux != NULL; aux = aux->prox) {
        fputs(aux->nome, contatosFile);
        fputs(aux->telefone, contatosFile);
        fputs(aux->endereco, contatosFile);
        fprintf(contatosFile, "%d\n", aux->cep);
        fputs(aux->dataDeNascimento, contatosFile);
        fputs("$\n", contatosFile);
    }
    fclose(contatosFile);
}