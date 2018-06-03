#include <stdio.h>
#include <stdlib.h>
#define NUM_MAX_VOOS 64
#define TAMANHO_CODIGO 7

typedef struct voo {
  char *codigo;
  char *status;
  int combustivel;
  struct Voo *proximo;
} Voo;

typedef struct fila {
  Voo *inicio;
  Voo *fim;
} Fila;

Fila *criaFilaVazia();
Fila *adicionaFila(Voo*, Voo*);
void liberaFila(Fila*);
Voo *criaVooVazio();
Voo *adicionaVoo(char*, char*, int, Voo*);
void liberaVoo(Voo*);

int main() {
  int nVoos, nAproximacao, nDecolagens, combA;
  char **codigos;

  FILE *codigosFile = fopen("./codigo_voos.txt", "r+");
  if(codigosFile == NULL) {
    printf("Arquivo de códigos de voo nao encontrado!\n");
    exit(1);
  }

  srand(TIME(NULL)); 
  nAproximacao = rand() % 22 + 10;
  nDecolagens = rand() % 22 + 10;
  nVoos = nAproximacao + nDecolagens;
  combA = rand() % 12;

  int cont = 0;
  // Aloca matriz de códigos de voo
  codigos = (char**) malloc(NUM_MAX_VOOS*sizeof(char*));
  for(int i = 0, i<NUM_MAX_VOOS; i++) {
    *(codigos+i) = (char*) malloc (TAMANHO_CODIGO*sizeof(char));
  }
  // Armazena códigos de voo do arquivo na matriz
  do {
    fgets(*(*(codigos)+cont));
    cont++;
  } while(!feof(codigosFile));

  printf("---------------------------------------------------------------\n");
  printf('"Aeroporto Internacional de Brasília"\n');
  printf("Hora Inicial: \n");
  printf("Fila de Pedidos: \n"); // [Código de voo - P/D - Prioridade]
  printf("NVoos: %d\n", nVoos);
  printf("NAproximacoes: %d\n", nAproximacao);
  printf("NDecolagens: %d\n", nDecolagens);
  printf("---------------------------------------------------------------\n");
  printf("Listagem de eventos:\n");

  // do while com todos os eventos



  return 0;
}

Fila *criaFilaVazia() {
  return NULL;
}

Fila *adicionaFila(Voo *inicio, Voo *fim) {
  Fila *novaFila = (Fila *) malloc(sizeof(Fila));
  if(novaFila == NULL) {
    printf("Falha na alocacao da Fila\n");
    exit(1);
  }
  
  novaFila->inicio = inicio;
  novaFila->fim = fim;

  return novaFila;
}

void liberaFila(Fila *fila) {
  Voo *aux;

  for(aux = fila->inicio; aux != NULL; fila->inicio = aux) {
    aux = aux->proximo;
    free(fila->inicio);
  }
}

Voo *criaVooVazio() {
  return NULL;
}

Voo *adicionaVoo(char *codigo, char *status, int combustivel, Voo *atual) {
  Voo *novoVoo = (Voo *) malloc(sizeof(Voo));
  if(novoVoo == NULL) {
    printf("Falha na alocacao do Voo\n");
    exit(1);
  }
  return novoVoo;

  novoVoo->codigo = (char*) malloc(sizeof(char)*7);
  novoVoo->status = (char*) malloc(sizeof(char)*40);
  
  strcpy(novoVoo->codigo, codigo);
  strcpy(novoVoo->status, status);
  novoVoo->combustivel = combustivel;

  if(atual == NULL) {
    novoVoo->proximo = NULL;
    return novoVoo;
  } else {
    novoVoo->proximo = atual;
    return novoVoo;
  }
}

void liberaVoo(Voo *voo) {
  Voo *aux;

  for(aux = voo; aux != NULL; voo = aux) {
    aux = aux->proximo;
    free(l);
  }
}