#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

// Cria um novo nó, retornando seu endereço
struct node* novo_no(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));//cria o nó a ser inserido
    temp->valor = item;//nó criado recebe o valor passado
    temp->esquerda = temp->direita = NULL;//ambos os ponteiros são iniciados como null, já que o nó inserido é folha
    return temp;//retorna o endereço do nó criado
}
 
// Inserir novo nó com determinado valor na árvore binária
struct node* inserir(struct node* node, int valor) {
    // Se a árvore (ou subárvore!) é vazia, então cria um novo nó
    if (node == NULL) {
        return novo_no(valor);//cria um novo nó; caso seja um nó folha, este endereço é retornado para sua chamada e o nó pai aponta para ele
    }
 
    // Caso contrário, faz uma busca pelo local adequado de inserção
    if (valor < node->valor) {
        node->esquerda = inserir(node->esquerda, valor);//chamada recursiva na subárvore esquerda
    } else if (valor > node->valor) {
        node->direita = inserir(node->direita, valor);//chamada recursiva na subárvore direita
    }
    
    // Retorna o ponteiro para o nó
    return node;
}

struct node *busca(struct node *raiz, int k){
    if(raiz==NULL || (*raiz).valor==k){//caso a árvore esteja vazia ou o valor esteja na raiz
        return raiz;
    }
    if((*raiz).valor > k){//percorre a subárvore esquerda
        return busca((*raiz).esquerda,k);
    }
    else{
        return busca((*raiz).direita,k);//percorre a subárvore direita
    }
}

// encontra o valor mínimo (aquele mais à esquerda) da árvore
struct node *min(struct node *raiz){
    while((*raiz).esquerda != NULL){
        raiz = (*raiz).esquerda;
    }
    return raiz;
}

//remove a raiz da árvore ou subárvore
struct node *removeRaiz(struct node *n){
    if (n == NULL) {//se o nó atual for nulo, retorna nulo
        return NULL;
    }
    
    if((*n).esquerda == NULL && (*n).direita == NULL){//se o nó atual não tiver nenhum filho, retorna nulo
        n = NULL;
        return NULL;//no caso de nenhum filho, o nó é simplesmente removido (o pai aponta pra NULL, se for o caso)
    }

    if((*n).esquerda == NULL){//se o nó só tiver o filho da direita, retorna ele
        return (*n).direita;//no caso de um único filho, este é colocado no lugar da raiz
    }

    if((*n).direita == NULL){//se o nó só tiver o filho da esquerda, retorna ele
        return (*n).esquerda;//no caso de um único filho, este é colocado no lugar da raiz
    }

    struct node *sucessor = min(n -> direita);//o próximo nó a ser inserido será o menor valor da subárvore direita
    n -> valor = sucessor -> valor;//sucessor passa para a raiz
    n -> direita = removeRaiz(sucessor);//o ponteiro da direita é a raiz modificada (caso ela tenha sido modificada) da subárvore direita

    return n;

}

//encontra o pai do nó
struct node* buscaPai(struct node *raiz, struct node *n, struct node *pai){
    if(raiz == NULL || (*raiz).valor == (*n).valor){//se a árvore for vazia ou o valor tiver sido encontrado, retorna o pai
        return pai;
    }

    pai = raiz;//raiz é definido como pai (assim percorre-se as subárvores)

    if((*raiz).valor > (*n).valor){//se o valor de n for menor que o da raiz, percorre subárvore esquerda
        return buscaPai((*raiz).esquerda, n, pai);
    }

    else{//se o valor de n for menor que o da raiz, percorre subárvore esquerda
        return buscaPai((*raiz).direita, n, pai);
    }
}

//remove o nó da árvore
struct node *removeNo(struct node *raiz, int valor){
    struct node *n = busca(raiz,valor);//encontra o endereço de n
    if(n){//se n != NULL (se n está na árvore)
        struct node *pai = buscaPai(raiz,n, NULL);//encontra o pai de n
        if(pai){//se n tiver pai
            if((*pai).direita == n){//se n for o filho da dureita
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

void construir(int V[], int p, int valor){
    V[p]=valor;
}

double arvore_binaria(int instancia_num, FILE *pontarq) {
    clock_t begin = clock(); //marca o horário de início

    // Define a árvore como uma estrutura vazia
    struct node* root = NULL;

    char line[16];//buffer do fgets

    while (fgets(line, sizeof(line), pontarq)) {//enquanto tem coisa para ler
        char comando; //guarda a letra do comando
        int num; //guarda o número a ser removido/inserido

        // Lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'I') //caso de inserção
                root = inserir(root, num);
            if (comando == 'R') //caso de remoção
                removeNo(root,num);
        }
    }
    
    clock_t end = clock(); //marca o horário de término
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

//-----------------------------------------------------------

struct node* inserirb(struct node* root2,int V[],int E, int D){
    struct node* no=malloc(sizeof(struct node));
    if(E>D){
        return NULL;
    }
    int mid=(E+D)/2;
    (*no).valor=V[mid];
    (*no).esquerda=inserirb(root2,V,E,mid-1);
    (*no).direita=inserirb(root2,V,mid+1,D);
    root2=no;
    return no;
}

double arvore_balanceada(int instancia_num, FILE *pontarq) {
    double tempo = 0;
    clock_t begin = clock();

    struct node* root2 = NULL;

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
                construir(V,cont,num);
                cont++;
            }
        }
    }
    
    inserirb(root2,V,0,sizeof(V));// Atualiza o root com o retorno da inserção
    
    while (fgets(line, sizeof(line), pontarq)) {
        char comando;
        int num;

        // Lê o comando e o número da linha
        if (sscanf(line, "%c %d", &comando, &num) == 2) {
            if (comando == 'R') {
                removeNo(root2,num);
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
        exit(1);
    }

    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    double tempo_n_balanceada = arvore_binaria(instancia_num, pontarq);

    pontarq = fopen(argv[1], "r");//corrompe sem isso

    if (pontarq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    //double tempo_balanceada = arvore_balanceada(instancia_num,pontarq);

    printf("%f\n", tempo_n_balanceada);

    return (1);
}
