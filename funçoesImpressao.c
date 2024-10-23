#include <stdlib.h>
#include "arvores.h"

//impressão em-ordem, usada para testes
void emordem(no* n) {
    if (n != NULL) {
        emordem(n -> esquerda);
        printf("%d ", n -> valor);
        emordem(n -> direita);
    }
}

//imprime a árvore em pré-ordem
void preordem(no *raiz){

    if(raiz != NULL){ //se a árvore não estiver vazia
        printf("%d ", raiz->valor); //imprime o valor do nó
        preordem(raiz->esquerda); //percorre a subárvore esquerda
        preordem(raiz->direita); //percorre a subárvore direita
    }
}
