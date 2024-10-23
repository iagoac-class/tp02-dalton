#include <stdlib.h>
#include "arvores.h"

//cria um novo nó, retornando seu endereço
no* novo_no(int val) {
    no* tmp = malloc(sizeof(no)); //um endereço na memória é reservado para o novo nó
    tmp -> valor = val; //o valor é o valor passado
    tmp -> esquerda = tmp -> direita = NULL; //ambos os ponteiros começam apontando para NULL (não apontam para nenhum nó)
    return tmp; //retorna o endereço do nó criado
}
 
//insere um valor na árvore, retorna a raiz
no* inserir(no* n, int val){
    if (n == NULL) //se a raiz for nula, este é o local para a inserçao, portanto retorne o ponteiro do nó criado com val
        return novo_no(val); //este nó será apontado pela variável de raiz da função de árvore balanceada ou pelo seu nó pai
    
    if (n -> valor == val)
        return n; //valores repetidos não são permitidos
    
    if (n -> valor < val) //se o valor do nó analisado for menor que val
        n -> direita = inserir(n -> direita, val); //percorre a subárvore à direita
    else //se o valor do nó analisado for maior que val
        n -> esquerda = inserir(n -> esquerda, val); //percorre a subárvore à esquerda

    return n; //retorna a raiz
}

//encontra o sucessor
no* encontra_prox(no* atual) {
    atual = atual -> direita; //entra na subárvore direita
    while (atual != NULL && atual -> esquerda != NULL) //enquanto houverem nós à esquerda
        atual = atual->esquerda; //anda para a esquerda
    return atual; //retorna o menor valor da subárvore direita
}

no* remove_no(no* raiz, int val) {
  
    if (raiz == NULL) //se a árvore estiver vazia
        return raiz; //retorna NULL

    if (raiz -> valor > val) //se o valor do nó analisado for maior do que val
        raiz -> esquerda = remove_no(raiz -> esquerda, val); //percorre a subárvore esquerda
    else if (raiz -> valor < val) //se o valor do nó analisado for menor do que val
        raiz -> direita = remove_no(raiz -> direita, val); //percorre a subárvore esquerda
    else { //se o valor do nó analisado for igual a val, este será o nó removido

        //raiz será removida
        if (raiz -> esquerda == NULL){ //se raiz não tem filho esquerdo
            no* tmp = raiz->direita; //guarda o filho direito temporariamente
            free(raiz); //remove raiz
            return tmp; //retorna o filho direito
        }

        if (raiz->direita == NULL){ //se raiz não tem filho direito
            no* tmp = raiz -> esquerda; //guarda o filho esquerdo temporariamente
            free(raiz); //remove raiz
            return tmp; //retorna o filho esquerdo
        }

        //se a raiz possui ambos os filhos
        no* prox = encontra_prox(raiz); //encontra o próximo valor
        raiz -> valor = prox -> valor; //valor de próximo salta para a raiz
        raiz -> direita = remove_no(raiz -> direita, prox -> valor); //nó com o valor de prox é removido
    }
    return raiz;
}

