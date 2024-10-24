#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvores.h"

double arvore_binaria(FILE *pontarq) {
    double tempo = 0; //variável que guarda o tempo
    clock_t begin = clock(); //registra o tempo de início de execução

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
            //emordem(raiz);
            //printf("\n");
        }
    }
    
    clock_t end = clock(); //registra o tempo de término da execução
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

//--------------------------------------------------------------------------------------

//retorna o tempo de execução das inserções e remoções na árvore balanceada
double arvore_balanceada(FILE *pontarq) {
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
        }
    }
    //preordem(raiz);
    //printf("\n");

    clock_t end = clock(); //registra o tempo de término da execução
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}




int main(int argc, char* argv[]){
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;

    //Leitor de instâncias
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores val\nonde val é um número entre 1 e 10 que simboliza a instância utilizada\n");
        return(0);
    }

    char caminho[256];// Buffer para armazenar o caminho completo do arquivo

    // Constrói o caminho para o arquivo dentro da pasta "instancias"
    snprintf(caminho, sizeof(caminho), "instancias/%s", argv[1]);

    //Abertura do arquivo para leitura
    FILE* pontarq = fopen(caminho, "r");
    if (pontarq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return(1);
    }
    
    double tempo_n_balanceada = arvore_binaria(pontarq);
    fclose(pontarq);//Fecha o arquivo de texto

    //Segunda abertura do arquivo para leitura
    pontarq = fopen(caminho, "r");//corrompe sem isso
    if (pontarq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return(1);
    }

    double tempo_balanceada = arvore_balanceada(pontarq);
    fclose(pontarq);//Fecha o arquivo de texto

    printf("%f\n", tempo_n_balanceada);
    printf("%f\n", tempo_balanceada);

    return (1);
}