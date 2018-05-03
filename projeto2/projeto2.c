#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//1 - Abre arquivo e armazena em uma matriz o valor de cada pixel da imagem
//2 OK - Função que rotacione um vetor, pegue o ultimo elemento do vetor e coloque como o primeiro elemento
//3 OK - Função que use a função de rotacionar para rotacionar-lo até voltar ao vetor inicial, e comparar o
//valor do vetor em decimal e armazenar o menor desses valores
//4 OK - Função que transforme um vetor de numeros binarios em um numero decimal
//5 - Cada pixel (8) deve ser comparado com seus vizinhos
//6 OK - Função que compare os pixels vizinhos e retorna uma matriz em que cada elemento será 0 ou 1,
//       onde 0 será se o valor do elemento correspondente for menor do que a média
//7 OK - Função que faça a media do valor dos elementos da matriz que representa um pixel
//8 - Função que faça a formula de contraste
//9 - Função que faça a formula de energia
//10 - Função que faça a formula de homogenidade
//11 OK - Função que sorteia 25 numeros de 50 para fazer parte do conjunto de treinamento
//13 - Função que conta a altura e largura de uma imagem

char *alocaVetorChar(int n); // tamanho do vetor, vetor a ser alocado
int *alocaVectorInt(int); // tamanho do vetor, vetor a ser alocado
int *alocaMatrizInt(int, int); //numero de linhas e colunas
float distanciaEuclidiana(int, int*, int*); // tamanho dos vetores, primeiro vetor, segundo vetor
int valorMinimo(int, int*); // tamanho do vetor, vetor
int valorMaximo(int, int*); // tamanho do vetor, vetor
int *normalizar(int, int*); // retorna o endereço do vetor normalizado e como entrada tamanho do vetor e vetor a ser normalizado
int binDecimal(int*, int); // retorna o valor em decimal e passa o vetor de binado como parametro
int rotacionaVetor(int*, int); // recebe o vetor a ser rotacionado e o tamanho do mesmo, retornando o vetor com menor valor decimal
float mediaMatriz(int*, int, int); // recebe a matriz e o tamanho de linhas e colunas da mesma, retornando a media do valor de seus elementos
int *transfMatriz(int*, int, int, float); // recebe uma matriz e o tamanho de linhas e colunas da mesma e a media dos seus elementos, retornando a matriz transformada em 0's e 1's
int *geraNumerosAleatorios(int, int); // recebe o valor minimo e o maximo do numero a ser gerado e retorna um vetor em que as posições do vetor que seja igual a 1 são os numeros gerados


int main () {
    int *p, *q, *f;
    int n = 2, i, j, u=9, lin=3, col=3;
    int *alturaAsp, *larguraAsp, *alturaGr, *larguraGr;
    int *pixels; //matriz que irá armazenar os dados de cada arquivo
    FILE **asphaltFiles = malloc(sizeof(FILE*) * (50));
    FILE **grassFiles = malloc(sizeof(FILE*) * (50));
    alturaAsp = alocaVectorInt(50);
    larguraAsp = alocaVectorInt(50);
    alturaGr = alocaVectorInt(50);
    larguraGr = alocaVectorInt(50);

    f = geraNumerosAleatorios(1, 50);

    // this for open and read the heigth/width of 25 files, that is the 25 for training
    for(i=0; i<1; i++){
        char asphalt[35];
        char grass[35];
        int auxNum = i+1;
        char aux[2];
        if(auxNum <= 9){
            sprintf(asphalt, "./DataSet/asphalt/asphalt_0%d.txt", auxNum);
            sprintf(grass, "./DataSet/grass/grass_0%d.txt", auxNum);
        } else {
            sprintf(asphalt, "./DataSet/asphalt/asphalt_%d.txt", auxNum);
            sprintf(grass, "./DataSet/grass/grass_%d.txt", auxNum);
        }

        *(asphaltFiles + i) = fopen( asphalt, "r");
        if(*(asphaltFiles + i) == NULL){
            printf("Falha em alocar os arquivos! \n");
            exit(1);
        }

        *(grassFiles + i) = fopen( grass, "r");
        if(*(grassFiles + i) == NULL){
            printf("Falha em alocar os arquivos! \n");
            exit(1);
        }
        char x;
        int stop = 0;
        *(larguraAsp + i) = 1; // largura começa com 1, pois o seu ultimo pixel da linha não possui o ';'
        do {
            fscanf(*(asphaltFiles + i), "%c", &x);
            if(x == ';' && stop == 0){
                *(larguraAsp + i) += 1;
            } else if (x == '\n'){
                *(alturaAsp + i) += 1;
                stop = 1;
            }
        } while (!feof(*(asphaltFiles + i)));
        *(alturaAsp + i) -= 1; // retirando 1 da altura, pois na sua ultima linha de pixel, possui um \n para uma linha vazia
        printf("Asphalt - Altura: %d, Largura: %d, Arquivo: %d\n", *(alturaAsp + i), *(larguraAsp + i), i+1);
        
        rewind(*(asphaltFiles + i));
        pixels = alocaMatrizInt(*(alturaAsp + i), *(larguraAsp + i));
        char aux2[] = "000";
        int y = 0, cont = 0;
        do{
            fscanf(*(asphaltFiles + i), "%c", &x);
            if(x == ';' || x == '\n'){
                y = 0;
                *(pixels + cont) = atoi(aux2);
                cont++;
            } else {
                aux2[y] = x;
                y++;
            }
        } while (!feof(*(asphaltFiles + i)));

        lin = *(alturaAsp + i);
        col = *(larguraAsp + i);
        int *matrizAux = alocaMatrizInt(3,3);
        int *matrizAuxBin;
        int auxK, auxJ;
        // começa em 1 e termina em x-1, pois não ira ler o primeira nem o ultima linha/coluna da matriz
        for(int k=1; k<(lin-1); k++){
            for(int j=1; j<(col-1); j++){
                auxK = k-1;
                auxJ = j-1;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxJ = j;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxJ = j+1;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxK = k;
                auxJ = j-1;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxJ = j;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxJ = j+1;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxK = k+1;
                auxJ = j-1;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxJ = j;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);
                auxJ = j+1;
                *(matrizAux+(auxK*3)+auxJ) = *(pixels+(k*col)+j);

                float mediaMatrizAux = mediaMatriz(matrizAux, 3, 3);
                matrizAuxBin = transfMatriz(matrizAux, 3, 3, mediaMatrizAux);

                int valorMinDecimal = rotacionaVetor(matrizAuxBin, 3*3);
            }
        }

        stop = 0;
        *(larguraGr + i) = 1; // largura começa com 1, pois o seu ultimo pixel da linha não possui o ';'
        do {
            fscanf(*(grassFiles + i), "%c", &x);
            if(x == ';' && stop == 0){
                *(larguraGr + i) += 1;
            } else if (x == '\n'){
                *(alturaGr + i) += 1;
                stop = 1;
            }
        } while (!feof(*(grassFiles + i)));
        *(alturaGr + i) -= 1; // retirando 1 da altura, pois na sua ultima linha de pixel, possui um \n para uma linha vazia
        printf("Grass - Altura: %d, Largura: %d, Arquivo: %d\n", *(alturaGr + i), *(larguraGr + i), i+1);
    }

    for(i=0; i<50; i++){
        fclose(*(asphaltFiles + i));
        fclose(*(grassFiles + i));
    }

    free(f);
    free(pixels);
    free(alturaAsp);
    free(larguraAsp);
    free(alturaGr);
    free(larguraGr);
    

    return 0;
}

char *alocaVetorChar(int n){
    char *vet = (char*) calloc(n, sizeof(char));
    if(vet == NULL){
        printf("Alocacao falhou. Finalizado. \n");
        exit(1);
    }
    return vet;
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

int *transfMatriz(int* m, int lin, int col, float media){
    int* matTransf;
    matTransf = alocaMatrizInt(lin, col);

    for(int i=0; i<lin; i++){
        for(int j=0; j<col; j++){
            if(*(m+(i*col)+j) > media){
                *(matTransf+(i*col)+j) = 1;
            } else {
                *(matTransf+(i*col)+j) = 0;
            }
        }
    }

    return matTransf;
}

int *geraNumerosAleatorios(int min, int max){
    int* vet, cont = 0;
    vet = alocaVectorInt(max);

    do{
        cont = 0;
        int numAleatorio = rand() % max;
        *(vet+(numAleatorio)) = 1;
        for(int i=0; i<max; i++){
            if(*(vet+i) == 1){
                cont++;
            }
        }
    }while(cont<25);

    return vet;
}