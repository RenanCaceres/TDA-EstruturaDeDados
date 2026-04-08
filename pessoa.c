#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pessoa.h"

#define MAX 100

// cria uma nova pessoa
Pessoa* pessoa_cria() {
    Pessoa* p = (Pessoa*) malloc(sizeof(Pessoa));
    if (p == NULL) {
        printf("Erro: sem memoria.\n");
        return NULL;
    }

    printf("Nome: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    printf("Idade: ");
    char buf[32];
    fgets(buf, sizeof(buf), stdin);
    p->idade = atoi(buf);

    printf("Endereco: ");
    fgets(p->endereco, sizeof(p->endereco), stdin);
    p->endereco[strcspn(p->endereco, "\n")] = '\0';

    printf("Pessoa criada! Tamanho alocado: %zu bytes\n", sizeof(Pessoa));
    return p;
}

// libera uma pessoa da memoria
void pessoa_libera(Pessoa* p) {
    if (p != NULL) {
        free(p);
        printf("Memoria liberada.\n");
    }
}

// imprime os dados de uma pessoa na tela
void pessoa_imprime(Pessoa* p, int indice) {
    if (p == NULL) return;
    printf("[%d] Nome: %s | Idade: %d | Endereco: %s\n",
           indice, p->nome, p->idade, p->endereco);
}

// atribui novos dados a uma pessoa
void pessoa_atribui(Pessoa* p) {
    if (p == NULL) return;

    printf("Novo nome: ");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';

    printf("Nova idade: ");
    char buf[32];
    fgets(buf, sizeof(buf), stdin);
    p->idade = atoi(buf);

    printf("Novo endereco: ");
    fgets(p->endereco, sizeof(p->endereco), stdin);
    p->endereco[strcspn(p->endereco, "\n")] = '\0';
}

// -------------------------------------------------------
// Funcoes do vetor (internas)
// -------------------------------------------------------

void inserir(Pessoa* vetor[], int* total) {
    if (*total >= MAX) {
        printf("Vetor cheio!\n");
        return;
    }

    vetor[*total] = pessoa_cria();

    if (vetor[*total] != NULL)
        (*total)++;
}

void listar(Pessoa* vetor[], int total) {
    if (total == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        pessoa_imprime(vetor[i], i + 1);
    }
}

void editar(Pessoa* vetor[], int total) {
    if (total == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    listar(vetor, total);

    char buf[32];
    int indice;
    printf("Qual numero deseja editar? ");
    fgets(buf, sizeof(buf), stdin);
    indice = atoi(buf);
    indice--;

    if (indice < 0 || indice >= total) {
        printf("Numero invalido.\n");
        return;
    }

    pessoa_atribui(vetor[indice]);
    printf("Pessoa atualizada!\n");
}

void remover(Pessoa* vetor[], int* total) {
    if (*total == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    listar(vetor, *total);

    char buf[32];
    int indice;
    printf("Qual numero deseja remover? ");
    fgets(buf, sizeof(buf), stdin);
    indice = atoi(buf);
    indice--;

    if (indice < 0 || indice >= *total) {
        printf("Numero invalido.\n");
        return;
    }

    pessoa_libera(vetor[indice]);

    for (int i = indice; i < *total - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    vetor[*total - 1] = NULL;
    (*total)--;

    printf("Pessoa removida!\n");
}

// -------------------------------------------------------
// Main
// -------------------------------------------------------

int main() {
    Pessoa* vetor[MAX];
    int total = 0;
    int opcao;

    for (int i = 0; i < MAX; i++) {
        vetor[i] = NULL;
    }

    do {
        printf("\n--------------------------------\n");
        printf("-       CADASTRO DE PESSOAS    -\n");
        printf("--------------------------------\n");
        printf("-  1 - Inserir pessoa          -\n");
        printf("-  2 - Listar pessoas          -\n");
        printf("-  3 - Editar pessoa           -\n");
        printf("-  4 - Remover pessoa          -\n");
        printf("-  0 - Sair                    -\n");
        printf("--------------------------------\n");
        char buf[32];
        fgets(buf, sizeof(buf), stdin);
        opcao = atoi(buf);

        if (opcao == 1) inserir(vetor, &total);
        if (opcao == 2) listar(vetor,  total);
        if (opcao == 3) editar(vetor,  total);
        if (opcao == 4) remover(vetor, &total);

    } while (opcao != 0);

    for (int i = 0; i < total; i++) {
        pessoa_libera(vetor[i]);
    }

    return 0;
}

