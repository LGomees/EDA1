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
Pessoa *ordenaLista(Pessoa *l);

int main () {
    Pessoa *contatos;
    contatos = criaListaVazia();
    int status;
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

    contatos = ordenaLista(contatos);

    do {
        printf("Escolha uma das opcoes seguintes:\n");
        printf("1 - Inserir novo registro\n");
        printf("2 - Remover registros que possuem certo nome\n");
        printf("3 - Visualizar registro a partir de nome\n");
        printf("4 - Visualizar todos os registros em ordem alfabetica de acordo com o nome\n");
        printf("5 - Sair\n");
        printf("Sua escolha: ");
        scanf("%d", &status);
        printf("\n");

        char novoNome[100];
        char novoTelefone[15] = "";
        char novoEndereco[100] = "";
        unsigned int novoCep;
        char novaDataDeNascimento[15] = "";
        int i = 0;

        int j, atual;
        char original[5] = "SDAGS";

        switch(status) {
            case 1:
                printf("Nome: ");
                scanf("%s", novoNome);
                printf("Telefone: ");
                scanf("%s", novoTelefone);
                printf("Endereco: ");
                scanf("%s", novoEndereco);
                printf("CEP: ");
                scanf("%u", &novoCep);
                printf("Data de Nascimento: ");
                scanf("%s", novaDataDeNascimento);
                strcat(novoNome, "\n");
                strcat(novoTelefone, "\n");
                strcat(novoEndereco, "\n");
                strcat(novaDataDeNascimento, "\n");
                contatos = insereInicio(contatos, novoNome, novoTelefone, \
                novoEndereco, novoCep, novaDataDeNascimento);
                printf("Preenchido com sucesso\n");
                printf("\n\n\n\n");
                contatos = ordenaLista(contatos);
                break;
            case 2:
                printf("Nome: ");
                scanf("%s", novoNome);
                contatos = removeContato(contatos, novoNome);
                printf("%s removido com sucesso!\n", novoNome);
                contatos = ordenaLista(contatos);
                break;
            case 3:
                printf("Nome: ");
                scanf("%s", novoNome);
                visualizaNome(contatos, novoNome);
                printf("%s removido com sucesso!\n", novoNome);
                break;
            case 4:
                imprime(contatos);
                break;
            case 5:
                printf("Programa encerrado!\n");
                break;
            default:
                printf("Escolha invalida, selecione uma opcao entre 1 e 5");
                break;
        }

    } while(status != 5);


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
        novo->ant = NULL;
        return novo;
    } else {
        novo->prox = l;
        l->ant = novo;
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

    for(aux = l; aux != NULL; aux = aux->prox) {
        printf("------------------------------\n");
        printf("Nome: %s\n", aux->nome);
        printf("Telefone: %s\n", aux->telefone);
        printf("Endereco: %s\n", aux->endereco);
        printf("CEP: %d\n", aux->cep);
        printf("Data de nascimento: %s\n", aux->dataDeNascimento);
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

Pessoa *ordenaLista(Pessoa *l) {
    int i, j;
    Pessoa *atual;
    atual = (Pessoa*) malloc(sizeof(Pessoa));
    if(atual == NULL) {
        printf("Erro na alocação!\n");
        exit(-1);
    }

    atual->nome = (char*) malloc(sizeof(char)*100);
    atual->telefone = (char*) malloc(sizeof(char)*15);
    atual->endereco = (char*) malloc(sizeof(char)*100);
    atual->dataDeNascimento = (char*) malloc(sizeof(char)*15);

    Pessoa *aux;
    Pessoa *aux2;

    for(aux = l->prox; aux != NULL; aux = aux->prox) {
        strcpy(atual->nome, aux->nome);
        strcpy(atual->telefone, aux->telefone);
        strcpy(atual->endereco, aux->endereco);
        atual->cep = aux->cep;
        strcpy(atual->dataDeNascimento, aux->dataDeNascimento);
        for (aux2 = aux->ant; aux2->ant != NULL && strcmp(atual->nome, aux2->nome) < 0; aux2 = aux2->ant) {
            strcpy(aux2->prox->nome, aux2->nome);
            strcpy(aux2->prox->telefone, aux2->telefone);
            strcpy(aux2->prox->endereco, aux2->endereco);
            aux2->prox->cep = aux2->cep;
            strcpy(aux2->prox->dataDeNascimento, aux2->dataDeNascimento);
        }
        strcpy(aux2->prox->nome, atual->nome);
        strcpy(aux2->prox->telefone, atual->telefone);
        strcpy(aux2->prox->endereco, atual->endereco);
        aux2->prox->cep = atual->cep;
        strcpy(aux2->prox->dataDeNascimento, atual->dataDeNascimento);
    }

    return l;
}