#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

// Cria um novo nó, retornando seu endereço
no* novo_no(int val) {
    no* tmp = malloc(sizeof(no));
    tmp -> valor = val;
    tmp -> esquerda = tmp -> direita = NULL;
    return tmp;
}
 
// Inserir novo nó com determinado valor na árvore binária
no* inserir(no* n, int val){
    if (n == NULL)
        return novo_no(val);
    
    if (n -> valor == val)
        return n;
    
    if (n -> valor < val)
        n -> direita = inserir(n -> direita, val);
    else
        n -> esquerda = inserir(n -> esquerda, val);

    // Return the (unchanged) n pointer
    return n;
}

no* encontra_prox(no* atual) {
    atual = atual -> direita;
    while (atual != NULL && atual -> esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

no* remove_no(no* raiz, int val) {
  
    if (raiz == NULL)
        return raiz;

    if (raiz -> valor > val)
        raiz -> esquerda = remove_no(raiz -> esquerda, val);
    else if (raiz -> valor < val)
        raiz -> direita = remove_no(raiz -> direita, val);
    else {

        if (raiz -> esquerda == NULL) {
            no* tmp = raiz->direita;
            free(raiz);
            return tmp;
        }

        // When raiz has onl y  esquerda child
        if (raiz->direita == NULL) {
            no* tmp = raiz -> esquerda;
            free(raiz);
            return tmp;
        }

        // When both children are present
        no* prox = encontra_prox(raiz);
        raiz -> valor = prox -> valor;
        raiz -> direita = remove_no(raiz -> direita, prox -> valor);
    }
    return raiz;
}

void emordem(no* n) {
    if (n != NULL) {
        emordem(n -> esquerda);
        printf("%d ", n -> valor);
        emordem(n -> direita);
    }
}

void posordem(no* n) {
    if(n != NULL) {
        posordem(n -> esquerda);
        posordem(n -> direita);
        printf("%d ", n -> valor);
    }
}

double arvore_binaria(int instancia_num, FILE *pontarq) {
    clock_t begin = clock(); //marca o horário de início

    //define a árvore como uma estrutura vazia
    no* raiz = NULL;

    char line[16]; //buffer do fgets

    while (fgets(line, sizeof(line), pontarq)) {//enquanto tem coisa para ler
        char comando; //guarda a letra do comando
        int num; //guarda o número a ser removido/inserido

        // Lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'I') //caso de inserção
                raiz = inserir(raiz, num);
            if (comando == 'R') //caso de remoção
                raiz = remove_no(raiz,num);
            // emordem(raiz);
            // printf("\n");
        }
    }
    
    clock_t end = clock(); //marca o horário de término
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

//--------------------------------------------------------------------

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

no* no_minimo(no* n){

    no* atual = n;

    while (atual->esquerda != NULL)
        atual = atual->esquerda;

    return atual;
}

no* remove_no_bin(no* raiz, int val){
    //DELEÇÃO
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
                tmp = raiz;
                raiz = NULL;
            }
            else //apenas um filho
             *raiz = *tmp; //filho substitui a raiz

            free(tmp);

        }else{ //dois filhos
            
            no* tmp = no_minimo(raiz->direita);

            raiz->valor = tmp->valor;

            raiz->direita = remove_no_bin(raiz->direita, tmp->valor);
        }
    }

    if (raiz == NULL) //se o nó removido era o único nó da árvore
      return raiz; //retorna nulo

    //ATUALIZAÇÃO DA ALTURA
    raiz->altura = 1 + maior(altura(raiz->esquerda), altura(raiz->direita));

    //VERIFICAÇÃO DO FATOR DE BALANCEAMENTO
    int bal = fb(raiz);


    // esquerda esquerda Case
    if (bal > 1 && fb(raiz->esquerda) >= 0)
        return rot_direita(raiz);

    // esquerda direita Case
    if (bal > 1 && fb(raiz->esquerda) < 0){
        raiz->esquerda =  rot_esquerda(raiz->esquerda);
        return rot_direita(raiz);
    }

    // direita direita Case
    if (bal < -1 && fb(raiz->direita) <= 0)
        return rot_esquerda(raiz);

    // direita esquerda Case
    if (bal < -1 && fb(raiz->direita) > 0){
        raiz->direita = rot_direita(raiz->direita);
        return rot_esquerda(raiz);
    }

    return raiz;
}

//imprime a árvore em pré-ordem
void preordem(no *raiz){

    if(raiz != NULL){ //se a árvore não estiver vazia
        printf("%d ", raiz->valor); //imprime o valor do nó
        preordem(raiz->esquerda); //percorre a subárvore esquerda
        preordem(raiz->direita); //percorre a subárvore direita
    }
}

//retorna o tempo de execução das inserções e remoções na árvore balanceada
double arvore_balanceada(int instancia_num, FILE *pontarq) {

    double tempo = 0; //variável que guarda o tempo
    clock_t begin = clock(); //registra o tempo de início de execução

    no* raiz = NULL; //raiz da árvore balanceada
    char line[16]; //buffer do fgets

    while (fgets(line, sizeof(line), pontarq)) { //enquanto tem coisa para ler

        char comando; //guarda a letra do comando
        int num; //guarda o número a ser removido/inserido

        if (sscanf(line, "%c %d", &comando, &num) == 2) { //lê o comando e o número da linha
            if (comando == 'I') //caso de inserção
                raiz = insere_bin(raiz, num);
            if (comando == 'R') //caso de remoção
                raiz = remove_no_bin(raiz, num);
            // emordem(raiz);
            // printf("\n");
        }
    }
    preordem(raiz);
    printf("\n");

    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}




int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;

    FILE* pontarq = fopen(argv[1], "r");

    if (pontarq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return(1);
    }

    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores val\nonde val é um número entre 1 e 10 que simboliza a instância utilizada\n");
        return(0);
    }
    
    double tempo_n_balanceada = arvore_binaria(instancia_num, pontarq);

    pontarq = fopen(argv[1], "r");//corrompe sem isso

    if (pontarq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return(1);
    }

    double tempo_balanceada = arvore_balanceada(instancia_num,pontarq);

    printf("%f, %f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}
