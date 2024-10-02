#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

// Cria um novo nó na árvore
struct node* novo_no(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->valor = item;
    temp->esquerda = temp->direita = NULL;
    return temp;
}
 
// Inserir novo nó com determinado
// valor na árvore binária
struct node* inserir(struct node* node, int valor) {
    // Se a árvore é vazia, então cria um novo nó
    if (node == NULL) {
        return novo_no(valor);
    }
 
    // Caso contrário, faz uma busca pelo local adequado de inserção
    if (valor < node->valor) {
        node->esquerda = inserir(node->esquerda, valor);
    } else if (valor > node->valor) {
        node->direita = inserir(node->direita, valor);
    }
    
    // Retorna o ponteiro para o nó
    return node;
}

struct node *busca(struct node *raiz, int k){
    if(raiz==NULL || (*raiz).valor==k){
        return raiz;
    }
    if((*raiz).valor > k){
        return busca((*raiz).esquerda,k);
    }
    else{
        return busca((*raiz).direita,k);
    }
}
struct node *buscaPai(struct node *raiz, struct node *n, struct node *pai){
    if(raiz==NULL || (*raiz).valor==(*n).valor){
        return pai;
    }
    pai=raiz;
    if((*raiz).valor > (*n).valor){
        return buscaPai((*raiz).esquerda,n,pai);
    }
    else{
        return buscaPai((*raiz).direita,n,pai);
    }
}

void remover(struct node* node, int valor){
    struct node* ant;
    if(node==NULL){
        return;
    }
    struct node* root=buscar(node,valor,&ant);
    if((*root).valor==valor){
        if((*root).direita==NULL && (*root).esquerda==NULL){
            (*ant).direita=NULL;
        }
        if((*root).direita!=NULL && (*root).esquerda!=NULL){
            (*ant).direita=(*root).direita;
        }
        if((*root).direita!=NULL){
            (*ant).direita=(*root).direita;
        }
        else{
            (*ant).esquerda=(*root).esquerda;
        }
        
    }
}

struct node *min(struct node *raiz){
    while((*raiz).esquerda!=NULL){
        raiz=(*raiz).esquerda;
    }
    return raiz;
}
struct node *removeRaiz(struct node *n){
    if (n == NULL) {
        return NULL;
    }
    
    if((*n).esquerda==NULL && (*n).direita==NULL){
        n=NULL;
        return NULL;
    }

    if((*n).esquerda==NULL){
        return (*n).direita;
    }
    if((*n).direita==NULL){
        return (*n).esquerda;
    }

    struct node *sucessor = min(n->direita);
    n->valor = sucessor->valor;
    n->direita = removeRaiz(sucessor);

    return n;

}
struct node *removeNo(struct node *raiz, int valor){
    struct node *n=busca(raiz,valor);
    if(n){
        struct node *gg=NULL;
        struct node *pai=buscaPai(raiz,n,gg);
        if(pai){
            if((*pai).direita==n){
                (*pai).direita=removeRaiz(n);
            }
            else{
                (*pai).esquerda=removeRaiz(n);
            }
        }
        else{
            raiz=removeRaiz(n);
        }
    }
    return raiz;
}

struct node* construir();

double arvore_binaria(int instancia_num, FILE *pontarq) {
    double tempo = 0;
    clock_t begin = clock();

    // Define a árvore como uma estrutura vazia
    struct node* root = NULL;

    int cont=0;
    int cont2=0;
    char line[256];
    while (fgets(line, sizeof(line), pontarq)) {
        char comando;
        int num;

        // Lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'I') {
                root = inserir(root, num); // Atualiza o root com o retorno da inserção
                cont++;
            }
            if (comando == 'R') {
                removeNo(root,num);
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

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    
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
        exit(1);
    }

    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    
    double tempo_n_balanceada = arvore_binaria(instancia_num,pontarq);
    //double tempo_balanceada = arvore_balanceada(instancia_num);

    

    
    printf("%f\n", tempo_n_balanceada);

    return (1);
}