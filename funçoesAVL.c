#include <stdlib.h>
#include "arvores.h"

//retorna a altura do nó passado como argumento
int altura(no* n){
    if(n == NULL) //se o não existir, retorne 0
        return 0;
    return n -> altura; //caso contrário retorne a altura
}

//retorna o maior número entre dois, usada para atualizar a altura de nós após a rotação
int maior(int x, int y){
    return (x > y)? x : y; //essa é uma forma reduzida de condicional, retorna x caso verdadeiro e y caso falso
}

//cria um novo nó a partir de um valor; nós-folha têm altura 1
no* novo_no_bin(int val){
    no* tmp = malloc(sizeof(no)); //um endereço na memória é reservado para o novo nó
    tmp -> valor = val; //o valor é o valor passado
    tmp -> esquerda = tmp -> direita = NULL; //ambos os ponteiros começam apontando para NULL (não apontam para nenhum nó)
    tmp -> altura = 1; //o nó é iniciado como altura 1, já que ele é um nó-folha
    return tmp; //retorna o endereço do nó criado
}

//rotação simples à direita em torno de uma raiz (a dupla também usa essa função), retorna a nova raiz
no* rot_direita(no* raiz){
    
    no* x = raiz -> esquerda; //x é o filho à esquerda da raiz
    no* y = x -> direita; //y é o filho à direita de x, que se tornará filho à esquerda da raiz (após a rotação)

    //ROTAÇÃO
    x -> direita = raiz; //x se torna a nova raiz e a raiz passa a ser seu filho à direita
    raiz -> esquerda = y; //o filho à direita de x é enviado para o outro lado da raiz, sendo filho à esquerda da antiga raiz

    //ATUALIZAÇÃO DAS ALTURAS
    raiz -> altura = maior(altura(raiz->esquerda), altura(raiz->direita)) + 1; //para o cálculo das alturas, apenas a maior entre os dois filhos é relevante
    x -> altura = maior(altura(x->esquerda), altura(x->direita)) + 1; //é somado 1, já que esses são os nós-pai

    return x; //nova raiz
}

//rotação simples à direita em torno de uma raiz (a dupla também usa essa função), retorna a nova raiz
no* rot_esquerda(no* raiz){

    no* y = raiz -> direita; //y é o filho à direita da raiz
    no* x = y -> esquerda; //x é o filho à esquerda de y, que se tornará filho à direita da raiz (após a rotação)

    //ROTAÇÃO
    y -> esquerda = raiz; //y se torna a nova raiz e raiz passa a ser seu filho à esquerda
    raiz -> direita = x; //o filho à esquerda de y é enviado para o outro lado da raiz, sendo filho à direita da antiga raiz

    //ATUALIZAÇÃO DAS ALTURAS
    raiz -> altura = maior(altura(raiz->esquerda), altura(raiz->direita)) + 1; //para o cálculo das alturas, apenas a maior entre os dois filhos é relevante
    y -> altura = maior(altura(y->esquerda), altura(y->direita)) + 1; //é somado 1, já que esses são os nós-pai

    return y; //nova raiz 
}

//retorna o fator de balanceamento da árvore passada
int fb(no* raiz){
    if(raiz == NULL) //se não houver árvore 
        return 0; //retorne 0
    return altura(raiz->esquerda) - altura(raiz->direita); //cálculo do fator de balanceamento
}

//insere um valor na árvore, retorna a raiz
no* insere_bin(no* n, int val) {

    //INSERÇÃO
    if (n == NULL) //se a raiz for nula, este é o local para a inserçao, portanto retorne o ponteiro do nó criado com val
        return novo_no_bin(val); //este nó será apontado pela variável de raiz da função de árvore balanceada ou pelo seu nó pai

    if (val < n->valor) //se o valor do nó analisado for maior que val
        n->esquerda = insere_bin(n->esquerda, val); //percorra a subárvore esquerda
    else if (val > n->valor) //senão, se o nó analisado for menor que val
        n->direita = insere_bin(n->direita, val); //percorra a subárvore direita
    else //valores iguais não são permitidos
        return n;

    //ATUALIZAÇÃO DA ALTURA
    n->altura = 1 + maior(altura(n->esquerda), altura(n->direita));

    //VERIFICAÇÃO DO FATOR DE BALANCEAMENTO
    int bal = fb(n);

    //ROTAÇÕES (CASO NECESSÁRIAS)

    // RSD (rotação simples à direita)
    if (bal > 1 && val < n->esquerda->valor) {
        return rot_direita(n); //retorna a nova raiz
    }

    // RSE (rotação simples à esquerda)
    if (bal < -1 && val > n->direita->valor) {
        return rot_esquerda(n); //retorna a nova raiz
    }

    // RDD (rotação dupla à direita)
    if (bal > 1 && val > n->esquerda->valor) {
        n->esquerda = rot_esquerda(n->esquerda); //duas rotações simples são feitas
        return rot_direita(n); //retorna a nova raiz
    }

    // RDE (rotação dupla à esquerda)
    if (bal < -1 && val < n->direita->valor) {
        n->direita = rot_direita(n->direita); //duas rotações simples são feitas
        return rot_esquerda(n); //retorna a nova raiz
    }

    return n; //retorna a raiz (no caso que não houve rotação)
}

//REMOÇÃO

//usada para encontrar o nó mínimo da subárvore direita durante a remoção
no* no_minimo(no* n){

    no* atual = n; //define o nó atual

    while (atual->esquerda != NULL) //enquanto houver nós à esquerda para percorrer
        atual = atual->esquerda; //anda para a esquerda

    return atual; //retorna o nó mais à esquerda (o menor)
}

//remove o nó e balancea a árvore caso necessário, retorna a raiz
no* remove_no_bin(no* raiz, int val){

    //REMOÇÃO
    if (raiz == NULL) //se a raiz for nula, este é o final da árvore/subárvore
        return raiz; //retorna nulo
    
    if (val < raiz->valor) //se o valor do nó analisado for maior que o valor a ser deletado
        raiz->esquerda = remove_no_bin(raiz->esquerda, val); //percorre a subárvore esquerda

    else if( val > raiz->valor) //se o valor do nó analisado for menor que o valor a ser deletado
        raiz->direita = remove_no_bin(raiz->direita, val); //percorre a subárvore direita

    else{ //se o valor do nó analisado for igual ao valor a ser deletado, esse nó será deletado

        //apenas um filho ou sem filhos
        if( (raiz->esquerda == NULL) || (raiz->direita == NULL) ){
            no* tmp = raiz->esquerda ? raiz->esquerda : raiz->direita; //se filho esquerdo for nulo, retorna filho direito, senão retorna filho esquerdo

            //sem filhos
            if (tmp == NULL){
                tmp = raiz; //o nó é simplesmente removido
                raiz = NULL;
            }
            else //apenas um filho
             *raiz = *tmp; //filho substitui a raiz

            free(tmp);

        }else{ //dois filhos
            
            no* tmp = no_minimo(raiz->direita); //este é o valor que substituirá o nó removido

            raiz->valor = tmp->valor; //valor de tmp passa para a raiz

            raiz->direita = remove_no_bin(raiz->direita, tmp->valor); //nó com tmp é removido
        }
    }

    if (raiz == NULL) //se o nó removido era o único nó da árvore
      return raiz; //retorna nulo

    //ATUALIZAÇÃO DA ALTURA
    raiz->altura = 1 + maior(altura(raiz->esquerda), altura(raiz->direita));

    //VERIFICAÇÃO DO FATOR DE BALANCEAMENTO
    int bal = fb(raiz);


    //caso esquerda-esquerda (RSD)
    if (bal > 1 && fb(raiz->esquerda) >= 0)
        return rot_direita(raiz);

    //caso esquerda-direita (RDD)
    if (bal > 1 && fb(raiz->esquerda) < 0){
        raiz->esquerda =  rot_esquerda(raiz->esquerda);
        return rot_direita(raiz);
    }

    //caso direita-direta (RSE)
    if (bal < -1 && fb(raiz->direita) <= 0)
        return rot_esquerda(raiz);

    //caso direita-esquerda (RDE)
    if (bal < -1 && fb(raiz->direita) > 0){
        raiz->direita = rot_direita(raiz->direita);
        return rot_esquerda(raiz);
    }

    return raiz;
}
