#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//1 - Abre arquivo e armazena em uma matriz o valor de cada pixel da imagem
//2 - Função que rotacione um vetor, pegue o ultimo elemento do vetor e coloque como o primeiro elemento
//3 - Função que use a função de rotacionar para rotacionar-lo até voltar ao vetor inicial, e comparar o 
//valor do vetor em decimal e armazenar o menor desses valores
//4 - Função que transforme um vetor de numeros binarios em um numero decimal
//5 - Cada pixel (8) deve ser comparado com seus vizinhos
//6 - Função que compare os pixels vizinhos e retorna uma matriz em que cada elemento será 0 ou 1, 
//onde 0 será se o valor do elemento correspondente for menor do que a média
//7 - Função que faça a media do valor dos elementos da matriz que representa um pixel

int *alocaVectorInt(int); // tamanho do vetor, vetor a ser alocado
float distanciaEuclidiana(int, int*, int*); // tamanho dos vetores, primeiro vetor, segundo vetor
int valorMinimo(int, int*); // tamanho do vetor, vetor
int valorMaximo(int, int*); // tamanho do vetor, vetor
int *normalizar(int, int*); // retorna o endereço do vetor normalizado e como entrada tamanho do vetor e vetor a ser normalizado

int main () {
    int *p, *q;
    float result = 0;
    int n = 2, i = 0;

    p = alocaVectorInt(n);
    q = alocaVectorInt(n);

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

int *alocaVectorInt(int n){
    int* vet = (int*) calloc(n, sizeof(int));
    if(vet == NULL){
        printf("Alocacao falhou. Finalizado. \n");
        exit(1);
    }
    return vet;
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

    return min;
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

    return max;
}

int *normalizar(int n, int* x){
    int *result, min, max;
    min = valorMinimo(n, x);
    max = valorMaximo(n, x);
    result = alocaVectorInt(n);

    for(int i=0; i<n; i++){
        *(result+i) = (*(x+i) - min) / (max - min);
    }
    return result;
}

