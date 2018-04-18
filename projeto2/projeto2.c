#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alocaVectorInt(int, int*);
float distanciaEuclidiana(int, int*, int*);

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

