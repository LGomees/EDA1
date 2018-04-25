#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//1 - Abre arquivo e armazena em uma matriz o valor de cada pixel da imagem
//2 OK - Função que rotacione um vetor, pegue o ultimo elemento do vetor e coloque como o primeiro elemento
//3 OK - Função que use a função de rotacionar para rotacionar-lo até voltar ao vetor inicial, e comparar o
//valor do vetor em decimal e armazenar o menor desses valores
//4 OK - Função que transforme um vetor de numeros binarios em um numero decimal
//5 - Cada pixel (8) deve ser comparado com seus vizinhos
//6 - Função que compare os pixels vizinhos e retorna uma matriz em que cada elemento será 0 ou 1,
//onde 0 será se o valor do elemento correspondente for menor do que a média
//7 - Função que faça a media do valor dos elementos da matriz que representa um pixel
//8 - Função que faça a formula de contraste
//9 - Função que faça a formula de energia
//10 - Função que faça a formula de homogenidade

int *alocaVectorInt(int); // tamanho do vetor, vetor a ser alocado
int *alocaMatrizInt(int, int); //numero de linhas e colunas
float distanciaEuclidiana(int, int*, int*); // tamanho dos vetores, primeiro vetor, segundo vetor
int valorMinimo(int, int*); // tamanho do vetor, vetor
int valorMaximo(int, int*); // tamanho do vetor, vetor
int *normalizar(int, int*); // retorna o endereço do vetor normalizado e como entrada tamanho do vetor e vetor a ser normalizado
int binDecimal(int*, int); // retorna o valor em decimal e passa o vetor de binado como parametro
int rotacionaVetor(int*, int); // recebe o vetor a ser rotacionado e o tamanho do mesmo, retornando o vetor com menor valor decimal
float mediaMatriz(int*, int, int); // recebe a matriz e o tamanho de linhas e colunas da mesma, retornando a media do valor de seus elementos

int main () {
    int *p, *q;
    float result = 0;
    int resultado = 0;
    int n = 2, i, j, k=9, lin=3, col=3;

    
    //result = mediaMatriz(p, lin, col);

    //resultado = rotacionaVetor(p, k);

    /*
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
    free(q);*/
    

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

int *alocaMatrizInt(int l, int c){
    int* matriz = (int*) calloc(l*c, sizeof(int));
    if(matriz == NULL){
        printf("Alocacao falhou. Finalizado \n");
        exit(1);
    }
    return matriz;
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

int binDecimal(int * v, int n){
    int result = 0;
    for(int i = 0; i<n; i++){
        result += *(v+n-i-1) * pow(2, i);
    }
    return result;
}

// 

int rotacionaVetor(int* v, int n){
    int aux, aux2, aux3, aux4, i, l, j, *vetorResult, result;

    vetorResult = alocaVectorInt(n);

    for(i = 0;i < n;i++){

      if(i==0){
        aux = *(v+i);
        aux2 = *(v+i+1);
        for(l=0;l<n;l++){
          if(l==0){
            *(v+l) = *(v+n-1);
            *(v+l+1) = aux;
          }
          if(l==1){
            aux = *(v+l+2);
            aux3 = *(v+l+1);
            *(v+l+1) = aux2;
            *(v+l+2) = aux3;
          }
          if (l>1){
            aux4 = *(v+l+2);
            *(v+l+2) = aux;
            aux = aux4;
          }
        }
        *(vetorResult) = binDecimal(v, n);
      }
      else{
        for(l=0;l<n;l++){
          if(l==0){
            aux = *(v+l);
            aux2 = *(v+l+1);
            *(v+l) = *(v+n-1);
            *(v+l+1) = aux;
          }
          if(l==1){
            aux = *(v+l+2);
            aux3 = *(v+l+1);
            *(v+l+1) = aux2;
            *(v+l+2) = aux3;
          }
          if (l>1){
            aux4 = *(v+l+2);
            *(v+l+2) = aux;
            aux = aux4;
          }
        }
        *(vetorResult+i) = binDecimal(v, n);
      }
    }
    result = valorMinimo(n, vetorResult);
    return result;
}

float mediaMatriz(int* m, int lin, int col){
    float resultado = 0.0f;
    for(int i=0; i<lin; i++){
        for(int j=0; j<col; j++){
            resultado += *(m+(i*col)+j);
        }
    }
    return (float)(resultado / (lin*col));
}