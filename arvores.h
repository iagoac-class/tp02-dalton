#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui

typedef struct no_ {
    int valor;
    struct no_ *esquerda;
    struct no_ *direita;
    int altura;
}no;

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

no* novo_no(int item);
no* inserir(no* n, int val);

no* remove_no(no *raiz, int valor);
void emordem(no* n);

int altura(no* n);
int maior(int x, int y);
no* novo_no_bin(int val);
no* rot_direita(no* raiz);
no* rot_esquerda(no* raiz);
int fb(no* n);
no* insere_bin(no* n, int val);
void preOrder(no *root);


double arvore_binaria(int instancia_num, FILE *pontarq);
double arvore_balanceada(int instancia_num, FILE *pontarq);

#endif // _H_ARVORES