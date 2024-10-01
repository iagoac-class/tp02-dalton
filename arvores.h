#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui

struct node {
    int valor;
    struct node *esquerda, *direita;
};

struct node* novo_no(int item);
struct node* inserir(struct node* node, int valor);
struct node* buscar(struct node* root, int valor);

double arvore_binaria(int instancia_num, FILE *pontarq);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES