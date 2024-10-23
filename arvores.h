#ifndef _H_ARVORES
#define _H_ARVORES
#include <stdio.h>

// Implementar qualquer struct que for necessária aqui

typedef struct no_ {
    int valor;
    struct no_ *esquerda;
    struct no_ *direita;
    int altura;
}no;

//funções de árvore binária
no* novo_no(int item);
no* inserir(no* n, int val);
no* remove_no(no *raiz, int valor);
void emordem(no* n); //para testes

//funções de árvore binária balanceada
int altura(no* n);
int maior(int x, int y);
no* novo_no_bin(int val);
no* rot_direita(no* raiz);
no* rot_esquerda(no* raiz);
int fb(no* n);
no* insere_bin(no* n, int val);
no* no_minimo(no* n);
no* remove_no_bin(no* raiz, int val);
void preordem(no *raiz); //para testes

double arvore_binaria(int instancia_num, FILE *pontarq);
double arvore_balanceada(int instancia_num, FILE *pontarq);

#endif // _H_ARVORES