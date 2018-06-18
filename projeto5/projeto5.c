#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct no {
    int value;
    struct no *left;
    struct no *right;
} No;

// Main functions
No *loadTreeFromFile(char* name_file); // Read file, create a tree, return the tree - OK
void showTree(No* tree); // Show the tree - OK
void isFull(No* tree); // Show if tree is full or not - OK
void searchValue(No* tree, int term); // Show nv No, value of father and value of brother(if exist) - OK
void getHeight(No* tree); // Show the height of the tree - OK
void removeValue(No* tree, int term); // Remove value of the tree, if don't exist, warn the user - OK
void printInOrder(No* tree); // Show tree in order
void printPreOrder(No* tree); // Show tree pre order
void printPostOrder(No* tree); // Show tree post order
void balanceTree(No* tree); // Check if the tree is balanced, if it's not, balance using rotation method
// Other functions
No *insert(No* tree, int value);
No *newNo(int term);
int getLevelUtil(No *tree, int term, int level);
bool printFather(No* tree, int term);
int height(No *tree);
bool isFullTree(No* tree);
No *minValue(No* tree);
No *delete(No* tree, int term);
void padding(char ch, int n);
void structure(No* tree, int level);
void printTreeRight(No* tree, int max_height, int level, char **m, int c_place);


int main() {
    No *tree;
    char name_file[4];
    int status;
    int valueSearch;
    printf("Digite o nome do arquivo a ser aberto: ");
    scanf("%s", name_file);
    tree = loadTreeFromFile(name_file);

    do {
        printf("Escolha uma das opcoes seguintes:\n");
        printf("1 - Mostrar arvore\n");
        printf("2 - Mostrar se a arvore e cheia ou nao\n");
        printf("3 - Procurar um valor dentro da arvore\n");
        printf("4 - Mostrar a altura da arvore\n");
        printf("5 - Remover valor da arvore\n");
        printf("6 - Imprimir com o algoritmo In Order\n");
        printf("7 - Imprimir com o algoritmo Pre Order\n");
        printf("8 - Imprimir com o algoritmo Post Order\n");
        printf("9 - Balancear arvore\n");
        printf("10 - Sair\n");
        printf("Sua escolha: ");
        scanf("%d", &status);
        printf("\n");

        switch(status) {
            case 1:
                showTree(tree);
                break;
            case 2:
                isFull(tree);
                break;
            case 3:
                printf("Digite o numero a ser procurado: ");
                scanf("%d", &valueSearch);
                searchValue(tree, valueSearch);
                break;
            case 4:
                getHeight(tree);
                break;
            case 5:
                printf("Digite o numero a ser deletado: ");
                scanf("%d", &valueSearch);
                removeValue(tree, valueSearch);
                break;
            case 6:
                printInOrder(tree);
                printf("\n");
                break;
            case 7:
                printPreOrder(tree);
                printf("\n");
                break;
            case 8:
                printPostOrder(tree);
                printf("\n");
                break;
            case 9:
                printf("Case 9\n");
                break;
            case 10:
                printf("Saindo...\n");
                break;
            default:
            printf("Opcao invalida, escolha uma opcao entre 1 e 10!\n");
                break;

        }
    } while(status != 10);

    return  0;
}

No *loadTreeFromFile(char* name_file) {
    No *tree = NULL;
    // createTree(tree);
    char *full_file_name = (char*) malloc(15*sizeof(char));
    sprintf(full_file_name, "./BSTs/%s.txt", name_file);
    FILE *file = fopen(full_file_name, "r+");
    if(file == NULL) {
        printf("Arquivo nao encontrado!!\n");
        exit(1);
    }

    char x;
    int *vetTree = (int*) malloc(10*sizeof(int));
    int y = 0, count = 0;
    char *aux = (char*) malloc(3*sizeof(char));

    do {
        fscanf(file, "%c", &x);
        if(x == ' ' || x == '\0') {
            y = 0;
            vetTree[count] = atoi(aux);
            memset(aux, ' ', 3);
            count++;
        } else {
            aux[y] = x;
            y++;
        }
    } while(count != 10);

    for(int i = 0; i<10; i++) {
        tree = insert(tree, vetTree[i]);
    }

    return tree;
}

void showTree(No* tree) {
    int max_height = height(tree);
    int rows_slashs = 0;
    for(int i=1; i<max_height; i++) {
        rows_slashs += pow(2, (max_height-i-1));
    }

    char **m_tree;
    int rows = max_height + rows_slashs;
    m_tree = (char**) malloc(rows*sizeof(char*));
    int columns = pow(2, max_height);
    for(int i=0; i<rows; i++) {
        *(m_tree+i) = (char*) malloc(columns*sizeof(char));
        memset(*(m_tree+i), ' ', columns);
    }

    if(max_height < 8) {
        printTreeRight(tree, max_height, 1, m_tree, 0);

        for(int i =0; i<rows; i++) {
            puts(*(m_tree+i));
        }
    } else {
        structure(tree, 0);
    }
    printf("\n\n");
}

void isFull(No* tree) {
    bool full = isFullTree(tree);
    if (full) {
        printf("A arvore e cheia\n\n\n");
    } else {
        printf("A arvore nao e cheia\n\n\n");
    }
}

void searchValue(No* tree, int term) {
    int level = getLevelUtil(tree, term, 1);
    if(level == 0) {
        printf("\nNumero nao encontrado!\n\n\n");
    } else {
        printf("\nO nivel do valor %d e %d\n", term, level);
        int father = printFather(tree, term);
        printf("\n\n");
    }
}

void getHeight(No *tree) {
    int n_height = height(tree);

    if(n_height == 0) {
        printf("Arvore vazia!\n");
    } else {
        printf("A arvore tem tamanho %d\n\n\n", n_height);
    }

}

void removeValue(No* tree, int term) {
    int level = getLevelUtil(tree, term, 1);
    if(level == 0) {
        printf("\nNumero nao encontrado!\n\n\n");
    } else {
        tree = delete(tree, term);
        printf("Numero deletado com sucesso!\n\n\n");
    }
}

void printInOrder(No *no) {
    if(no != NULL) {
        printInOrder(no->left);
        printf("\n%d", no->value);
        printInOrder(no->right);
    }
}

void printPreOrder(No *no) {
    if(no != NULL) {
        printf("\n%d", no->value);
        printPreOrder(no->left);
        printPreOrder(no->right);
    }
}

void printPostOrder(No *no) {
    if(no != NULL) {
        printPostOrder(no->left);
        printPostOrder(no->right);
        printf("\n%d", no->value);
    }
}


No *newNo(int term) {
    No *temp = (No*) malloc(sizeof(No));
    temp->value = term;
    temp->left = temp->right = NULL;
    return temp;
}

No *insert(No* tree, int value) {
    if (tree == NULL) return newNo(value);

    if (value < tree->value) {
        tree->left = insert(tree->left, value);
    } else if (value > tree->value) {
        tree->right = insert(tree->right, value);
    }
    return tree;
}

int getLevelUtil(No *tree, int term, int level) {
    if (tree == NULL) {
        return 0;
    }
    if (tree->value == term) {
        return level;
    }

    int downlevel = getLevelUtil(tree->left, term, level+1);
    if (downlevel != 0) {
        return downlevel;
    }
    downlevel = getLevelUtil(tree->right, term, level+1);
    return downlevel;
}

bool printFather(No* tree, int term) {
    if(tree == NULL) {
        return false;
    }
    if(tree->value == term) {
        return true;
    }
    if(printFather(tree->left, term)) {
        if(tree->right != NULL) {
            printf("O pai e %d e o irmao e %d", tree->value, tree->right->value);
        } else {
            printf("O pai e %d e nao possui irmao", tree->value);
        }
        return false;
    } else if(printFather(tree->right, term)) {
        if(tree->left != NULL) {
            printf("O pai e %d e o irmao e %d", tree->value, tree->left->value);
        } else {
            printf("O pai e %d e nao possui irmao", tree->value);
        }
        return false;
    }
    return false;
}

int height(No *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        int lH = height(tree->left);
        int rH = height(tree->right);

        if (lH > rH) {
            return (lH + 1);
        } else {
            return (rH + 1);
        }
    }
}

bool isFullTree(No* tree) {
    if (tree == NULL) {
        return true;
    }
    if (tree->left == NULL && tree->right == NULL) {
        return true;
    }
    if ((tree->left) && (tree->right)) {
        return (isFullTree(tree->left) && isFullTree(tree->right));
    }
    return false;
}

No *minValue(No* tree) {
    No *aux = tree;

    while (aux->left != NULL) {
        aux = aux->left;
    }

    return aux;
}

No *delete(No* tree, int term) {
    if (tree == NULL) {
        return tree;
    }
    if (term < tree->value) {
        tree->left = delete(tree->left, term);
    } else if (term > tree->value) {
        tree->right = delete(tree->right, term);
    } else {
        if(tree->left == NULL) {
            No *temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            No *temp = tree->left;
            free(tree);
            return temp;
        }

        No *temp = minValue(tree->right);
        tree->value = temp->value;
        tree->right = delete(tree->right, temp->value);         
    }
    return tree;
}

void padding(char ch, int n) {
    for(int i=0; i<n; i++) {
        putchar(ch);
    }
}

void structure(No* tree, int level) {
    int i;

    if(tree == NULL) {
        padding('\t', level);
        puts("~");
    } else {
        structure(tree->right, level + 1);
        padding('\t', level);
        printf("%d\n", tree->value);
        structure(tree->left, level + 1);
    }
}

void printTreeRight(No* tree, int max_height, int level, char** m, int c_place) {
    if(tree != NULL) {
        int place = 0;
        int c_slashs = pow(2, max_height-level-1);
        int depth = 0;
        for(int i=1; i<level; i++) {
            depth += pow(2, max_height-i-1);
        }
        
        if(level == 1) {
            place = pow(2, max_height-level);
            c_place = place;
            int c_place_r = c_place, c_place_l = c_place;

            char *num = (char*) malloc(3*sizeof(char));
            snprintf(num, 3, "%d", tree->value);
            puts(num);
            if(strlen(num) == 1) {
                *(*(m)+place) = num[0];
            } else if (strlen(num) == 2) {
                *(*(m)+place) = num[0];
                *(*(m)+place+1) = num[1];
            } else {
                *(*(m)+place-1) = num[0];
                *(*(m)+place) = num[1];
                *(*(m)+place+1) = num[2];
            }

            for(int i=1; i<c_slashs+1; i++) {
                if(tree->left != NULL) {
                    *(*(m+depth+level+i-1)+place-i) = '/';
                    c_place_l--;
                }
                if(tree->right != NULL) {
                    *(*(m+depth+level+i-1)+place+i) = '\\';
                    c_place_r++;
                }
            }
            
            printTreeRight(tree->left, max_height, level+1, m, c_place_l);
            printTreeRight(tree->right, max_height, level+1, m, c_place_r);

        } else {
            place = c_place;
            int c_place_r = c_place, c_place_l = c_place;

            char *num = (char*) malloc(3*sizeof(char));
            snprintf(num, 3, "%d", tree->value);
            puts(num);
            if(strlen(num) == 1) {
                *(*(m+depth+level-1)+place) = num[0];
            } else if (strlen(num) == 2) {
                *(*(m+depth+level-1)+place) = num[0];
                *(*(m+depth+level-1)+place+1) = num[1];
            } else {
                *(*(m+depth+level-1)+place-1) = num[0];
                *(*(m+depth+level-1)+place) = num[1];
                *(*(m+depth+level-1)+place+1) = num[2];
            }

            if(level != max_height) {
                for(int i=1; i<c_slashs+1; i++) {
                    if(tree->left != NULL) {
                        *(*(m+depth+level+i-1)+place-i) = '/';
                        c_place_l--;
                    }
                    if(tree->right != NULL) {
                        *(*(m+depth+level+i-1)+place+i) = '\\';
                        c_place_r++;
                    }
                }
            }

            printTreeRight(tree->left, max_height, level+1, m, c_place_l);
            printTreeRight(tree->right, max_height, level+1, m, c_place_r);
        }
    }
}

