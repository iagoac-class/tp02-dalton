#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui

typedef struct no_ {
    int valor;
    struct no_ *esquerda, *direita;
}no;

no* novo_no(int item);
no* inserir(no* n, int val);

no* remove_no(no *raiz, int valor);
void emordem(no* n);

no* inserirb(no* root2,int V[],int E, int D);

double arvore_binaria(int instancia_num, FILE *pontarq);
double arvore_balanceada(int instancia_num, FILE *pontarq);

#endif // _H_ARVORES