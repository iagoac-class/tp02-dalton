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

int altura(no* n){
    if(n == NULL)
        return 0;
    return n -> altura;
}

int maior(int x, int y){
    return (x > y)? x : y;
}


no* novo_no_bin(int val){
    no* tmp = malloc(sizeof(no));
    tmp -> valor = val;
    tmp -> esquerda = NULL;
    tmp -> direita = NULL;
    tmp -> altura = 1;
    return tmp;
}

no* rot_direita(no* raiz){
    no* x = raiz -> esquerda;
    no* y = x -> direita;

    //rotação
    x -> direita = raiz;
    raiz -> esquerda = y;

    //atualizar alturas
    raiz -> altura = maior(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    x -> altura = maior(altura(x->esquerda), altura(x->direita)) + 1;

    return x; //nova raiz 
}

no* rot_esquerda(no* raiz){
    no* y = raiz -> direita;
    no* x = y -> esquerda;

    //rotação
    y -> esquerda = raiz;
    raiz -> direita = x;

    //atualizar alturas
    raiz -> altura = maior(altura(raiz->esquerda), altura(raiz->direita)) + 1;
    y -> altura = maior(altura(y->esquerda), altura(y->direita)) + 1;

    return y; //nova raiz 
}

int fb(no* n){
    if(n == NULL)
        return 0;
    return altura(n->esquerda) - altura(n->direita);
}

// Função para inserir um valor na árvore
no* insere_bin(no* n, int val) {
    // Inserção normal
    if (n == NULL)
        return novo_no_bin(val);

    if (val < n->valor)
        n->esquerda = insere_bin(n->esquerda, val);
    else if (val > n->valor)
        n->direita = insere_bin(n->direita, val);
    else // Valores iguais não são permitidos
        return n;

    // Atualizar a altura de n
    n->altura = 1 + maior(altura(n->esquerda), altura(n->direita));

    // Verificar balanceamento de n
    int bal = fb(n);

    // RSD (Right Single Rotation)
    if (bal > 1 && val < n->esquerda->valor) {
        return rot_direita(n);
    }

    // RSE (Left Single Rotation)
    if (bal < -1 && val > n->direita->valor) {
        return rot_esquerda(n);
    }

    // RDD (Right Double Rotation)
    if (bal > 1 && val > n->esquerda->valor) {
        n->esquerda = rot_esquerda(n->esquerda);
        return rot_direita(n);
    }

    // RDE (Left Double Rotation)
    if (bal < -1 && val < n->direita->valor) {
        n->direita = rot_direita(n->direita);
        return rot_esquerda(n);
    }

    // Retorna o ponteiro n
    return n;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints altura of every node
void preOrder(no *root)
{
    if(root != NULL)
    {
        printf("%d ", root->valor);
        preOrder(root->esquerda);
        preOrder(root->direita);
    }
}

double arvore_balanceada(int instancia_num, FILE *pontarq) {
    double tempo = 0;
    clock_t begin = clock();

    no* raiz2 = NULL;
    char line[16]; //buffer do fgets

    while (fgets(line, sizeof(line), pontarq)) {//enquanto tem coisa para ler
        char comando; //guarda a letra do comando
        int num; //guarda o número a ser removido/inserido

        //lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'I') //caso de inserção
                raiz2 = insere_bin(raiz2, num);
            //if (comando == 'R') //caso de remoção
                // raiz2 = remove_bin(raiz2, num);
        }
    }
    preOrder(raiz2);

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
        printf("Para evalecutar o código, digite ./arvores val\nonde val é um número entre 1 e 10 que simboliza a instância utilizada\n");
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
