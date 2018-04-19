#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alocaVectorInt(int, int*); // tamanho do vetor, vetor a ser alocado
float distanciaEuclidiana(int, int*, int*); // tamanho dos vetores, primeiro vetor, segundo vetor
int valorMinimo(int, int*); // tamanho do vetor, vetor
int valorMaximo(int, int*); // tamanho do vetor, vetor
int *normalizar(int, int*); // retorna o vetor normalizado e como entrada tamanho do vetor e vetor a ser normalizado

int main () {
    int *p, *q;
    float result = 0;
    int n = 2, i = 0;
    //alocaVectorInt(n, p);
    //alocaVectorInt(n, q);

    p = (int*) calloc(n, sizeof(int));
    if(p == NULL){
        printf("Alocacao falhou. Finalizado. \n");
        exit(1);
    }

    q = (int*) calloc(n, sizeof(int));
    if(q == NULL){
        printf("Alocacao falhou. Finalizado. \n");
        exit(1);
    }

    for(i=0; i<n; i++){
        printf("Digite o termo %d de p: ", i);
        scanf("%d", p+i);
        printf("Digite o termo %d de q: ", i);
        scanf("%d", q+i);
    }

    result = distanciaEuclidiana(n, p, q);

    printf("%.2f \n", result);

    free(p);
    free(q);

    return 0;
}

void alocaVectorInt(int n, int* p){
    p = (int*) calloc(n, sizeof(int));
    if(p == NULL){
        printf("Alocacao falhou. Finalizado. \n");
        exit(1);
    }
}

float distanciaEuclidiana(int n, int* p, int* q) {
    float result = 0;
    for(int i=0; i<n; i++){
        result += pow((*(p+i) - *(q+i)), 2);
    }
    return sqrt(result);
}

int valorMinimo(int n, int* x){
    int min;
    for(int i=0; i<n; i++){
        if(i==0){
            min = *(x+i);
        }
        else if(*(x+i) < min){
            min = *(x+i);
        }
    }
}

int valorMaximo(int n, int* x){
    int max;
    for(int i=0; i<n; i++){
        if(i==0){
            max = *(x+i);
        }
        else if(*(x+i) > max){
            max = *(x+i);
        }
    }
}

int *normalizar(int n, int* x){
    int *result, min, max;
    min = valorMinimo(n, x);
    max = valorMaximo(n, x);
    result = (int*) calloc(n, sizeof(int));
    if(result == NULL){
        printf("Alocacao falhou. Finalizado. \n");
        exit(1);
    }

    for(int i=0; i<n; i++){
        *(result+i) = (*(x+i) - min) / (max - min);
    }
    return result;
}

