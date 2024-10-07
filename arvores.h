#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui

struct node {
    int valor;
    struct node *esquerda, *direita;
};

struct node* novo_no(int item);
struct node* inserir(struct node* node, int valor);
struct node *busca(struct node *raiz, int k);

struct node *min(struct node *raiz);
struct node *removeRaiz(struct node *n);
struct node *removeNo(struct node *raiz, int valor);

void construir(int V[], int p, int valor);
struct node* inserirb(struct node* root2,int V[],int E, int D);

double arvore_binaria(int instancia_num, FILE *pontarq);
double arvore_balanceada(int instancia_num, FILE *pontarq);

#endif // _H_ARVORES