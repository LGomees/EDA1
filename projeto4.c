#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define NUM_MAX_VOOS 64
#define TAMANHO_CODIGO 7

typedef struct voo {
  char codigo[7];
  char status;
  int combustivel;
  struct voo *proximo;
} Voo;

typedef struct fila {
  Voo *inicio;
  Voo *fim;
} Fila;

Fila *criaFilaVazia();
Fila *adicionaFila(Voo*, Voo*);
void liberaFila(Fila*);
Voo *criaVooVazio();
Voo *adicionaVoo(char*, char, int, Voo*);
void liberaVoo(Voo*);
void finalAdicionaVoo(int*, char, int, int, char*);
void imprimeVoos(Voo*);

// Aproximação 1*UnTempo     Pouso 3*UnTempo     Decolagem 2*UnTempo

int main() {
  int nVoos, nAproximacao, nDecolagens, combA;
  int UnTempo = 50;
  char pistas[3];
  char *codigos;
  Voo *voos = criaVooVazio();
  Fila *fila = criaFilaVazia();

  FILE *codigosFile = fopen("./codigo_voos.txt", "r+");
  if(codigosFile == NULL) {
    printf("Arquivo de códigos de voo nao encontrado!\n");
    exit(1);
  }

  srand(time(NULL)); 
  nAproximacao = rand() % 22 + 10;
  nDecolagens = rand() % 22 + 10;
  nVoos = nAproximacao + nDecolagens;

  int cont = 0;
  codigos = (char*) malloc(TAMANHO_CODIGO*sizeof(char));

  // do while com todos os eventos
  // pista 3: Decolagens, pista 1,2 tanto para pouso quanto para decolagem
  int tempo = 0;
  cont = 0;
  Voo *vooInicial;

  // Cria voos de aproximação
  for(int i=0; i<nAproximacao; i++) {
    combA = rand() % 12;
    fgets(codigos, 7, codigosFile);
    voos = adicionaVoo(codigos, 'A', combA, voos);
  }

  // Cria voos de decolagem
  for(int i=0; i<nDecolagens; i++) {
    combA = rand() % 12;
    fgets(codigos, 7, codigosFile);
    voos = adicionaVoo(codigos, 'D', combA, voos);

    if (i == 0) {
      vooInicial = voos;
    }
  }

  fila = adicionaFila(vooInicial, voos);

  printf("---------------------------------------------------------------\n");
  printf("Aeroporto Internacional de Brasília\n");
  printf("Hora Inicial: %d minutos\n", tempo);
  printf("Fila de Pedidos: \n");
  imprimeVoos(voos);
  printf("NVoos: %d\n", nVoos);
  printf("NAproximacoes: %d\n", nAproximacao);
  printf("NDecolagens: %d\n", nDecolagens);
  printf("---------------------------------------------------------------\n");
  printf("Listagem de eventos:\n");
  
  do {
    tempo = cont*UnTempo;

    // Pista 1
    finalAdicionaVoo(&nVoos, voos->status, tempo, 1, voos->codigo);
    voos = voos->proximo->proximo;
    fila = adicionaFila(voos, vooInicial);
    
    // Pista 2
    finalAdicionaVoo(&nVoos, voos->status, tempo, 2, voos->codigo);
    voos = voos->proximo->proximo;
    fila = adicionaFila(voos, vooInicial);

    // Pista 3
    finalAdicionaVoo(&nVoos, voos->status, tempo, 3, voos->codigo);
    voos = voos->proximo->proximo;
    fila = adicionaFila(voos, vooInicial);

    cont++;
  } while(cont != nVoos);



  return 0;
}

void imprimeVoos(Voo *voo) {
  Voo *aux;

  for(aux = voo; aux != NULL; aux = aux->proximo) {
    printf("%s", aux->codigo);
  }
  printf("\n\n");
}

void finalAdicionaVoo(int* nVoos, char status, int tempo, int nPista, char *codigo) {
  if(status == 'P') {
    (*nVoos)--;
    printf("\n");
    printf("Codigo do voo: %s", codigo);
    printf("Status: Aeronave pousou\n");
    printf("Horario do inicio do procedimento: %d minutos\n", tempo);
    printf("Numero da pista: %d\n", nPista);
  } else if(status == 'D') {
    printf("\n");
    printf("Codigo do voo: %s\n", codigo);
    printf("Status: Aeronave decolou\n");
    printf("Horario do inicio do procedimento: %d minutos\n", tempo);
    printf("Numero da pista: %d\n", nPista);
  }
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

Voo *adicionaVoo(char *codigo, char status, int combustivel, Voo *atual) {
  Voo *novoVoo = (Voo *) malloc(sizeof(Voo));
  if(novoVoo == NULL) {
    printf("Falha na alocacao do Voo\n");
    exit(1);
  }

  //novoVoo->codigo = (char*) malloc(sizeof(char)*7);
  
  strcpy(novoVoo->codigo, codigo);
  novoVoo->status = status;
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
    free(voo);
  }
}