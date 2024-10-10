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

    // Return the (unchanged) node pointer
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

double arvore_binaria(int instancia_num, FILE *pontarq) {
    clock_t begin = clock(); //marca o horário de início

    // Define a árvore como uma estrutura vazia
    no* raiz = NULL;

    char line[16];//buffer do fgets

    while (fgets(line, sizeof(line), pontarq)) {//enquanto tem coisa para ler
        char comando; //guarda a letra do comando
        int num; //guarda o número a ser removido/inserido

        // Lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'I') //caso de inserção
                raiz = inserir(raiz, num);
            if (comando == 'R') //caso de remoção
                raiz = remove_no(raiz,num);
            //emordem(raiz);
            //printf("\n");
        }
    }
    
    clock_t end = clock(); //marca o horário de término
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

//-----------------------------------------------------------

no* inserirb(no* raiz2,int V[],int E, int D){
    no* no=malloc(sizeof(no));
    if(E>D){
        return NULL;
    }
    int mid=(E+D)/2;
    (*no).valor=V[mid];
    (*no).esquerda=inserirb(raiz2,V,E,mid-1);
    (*no).direita=inserirb(raiz2,V,mid+1,D);
    raiz2=no;
    return no;
}

double arvore_balanceada(int instancia_num, FILE *pontarq) {
    double tempo = 0;
    clock_t begin = clock();

    no* raiz2 = NULL;

    int cont=0;
    int cont2=0;
    int V[20000];
    char line[256];

    while (fgets(line, sizeof(line), pontarq)) {
        char comando;
        int num;

        // Lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'I') {
                // construir(V,cont,num);
                cont++;
            }
        }
    }
    
    inserirb(raiz2,V,0,sizeof(V));// Atualiza o raiz com o retorno da inserção
    
    while (fgets(line, sizeof(line), pontarq)) {
        char comando;
        int num;

        // Lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'R') {
                // removeNo(raiz2,num);
                cont2++;
            }
        }
    }
    printf("\nContador1: %d Contador2: %d\n", cont, cont2);

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

    //double tempo_balanceada = arvore_balanceada(instancia_num,pontarq);

    printf("%f\n", tempo_n_balanceada);

    return (1);
}
