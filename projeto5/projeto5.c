#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int value;
    struct no *esquerda;
    struct no *direita;
} No;

No *loadTreeFromFile(char* name_file); // Read file, create a tree, return the tree
void showTree(No* tree); // Show the tree
void isFull(No* tree); // Show if tree is full or not
void searchValue(No* tree, int term); // Show nv No, value of father and value of brother(if exist)
void getHeight(No* tree); // Show the height of the tree
void removeValue(No* tree, int term); // Remove value of the tree, if don't exist, warn the user
void printInOrder(No* tree); // Show tree in order
void printPreOrder(No* tree); // Show tree pre order
void printPostOrder(No* tree); // Show tree post order
void balanceTree(No* tree); // Check if the tree is balanced, if it's not, balance using rotation method

int main() {

    return  0;
}