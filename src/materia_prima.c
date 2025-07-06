#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "materia_prima.h"
#include "utils.h"

// Função utilitária de altura e balanceamento AVL
int altura(MateriaPrima* n) {
    if (!n) return 0;
    int h_esq = altura(n->esq);
    int h_dir = altura(n->dir);
    return 1 + (h_esq > h_dir ? h_esq : h_dir);
}

int fator_balanceamento(MateriaPrima* n) {
    return altura(n->esq) - altura(n->dir);
}

// Rotação simples e dupla
MateriaPrima* rotacao_direita(MateriaPrima* y) {
    MateriaPrima* x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    return x;
}

MateriaPrima* rotacao_esquerda(MateriaPrima* x) {
    MateriaPrima* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    return y;
}

MateriaPrima* balancear(MateriaPrima* raiz) {
    if (!raiz) return NULL;
    int fb = fator_balanceamento(raiz);

    if (fb > 1) {
        if (fator_balanceamento(raiz->esq) < 0)
            raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }
    if (fb < -1) {
        if (fator_balanceamento(raiz->dir) > 0)
            raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }
    return raiz;
}

// CRUD na árvore AVL
MateriaPrima* inserir_materia_prima(MateriaPrima* raiz, int codigo, const char* nome, float preco) {
    if (!raiz) {
        MateriaPrima* nova = malloc(sizeof(MateriaPrima));
        nova->codigo = codigo;
        strcpy(nova->nome, nome);
        nova->preco = preco;
        nova->esq = nova->dir = NULL;
        return nova;
    }
    if (codigo < raiz->codigo)
        raiz->esq = inserir_materia_prima(raiz->esq, codigo, nome, preco);
    else if (codigo > raiz->codigo)
        raiz->dir = inserir_materia_prima(raiz->dir, codigo, nome, preco);
    else
        raiz->preco = preco; // atualiza preço se já existir
    return balancear(raiz);
}

MateriaPrima* buscar_materia_prima(MateriaPrima* raiz, int codigo) {
    if (!raiz) return NULL;
    if (codigo < raiz->codigo) return buscar_materia_prima(raiz->esq, codigo);
    if (codigo > raiz->codigo) return buscar_materia_prima(raiz->dir, codigo);
    return raiz;
}

MateriaPrima* menor(MateriaPrima* n) {
    while (n->esq) n = n->esq;
    return n;
}

MateriaPrima* remover_materia_prima(MateriaPrima* raiz, int codigo) {
    if (!raiz) return NULL;
    if (codigo < raiz->codigo)
        raiz->esq = remover_materia_prima(raiz->esq, codigo);
    else if (codigo > raiz->codigo)
        raiz->dir = remover_materia_prima(raiz->dir, codigo);
    else {
        if (!raiz->esq) {
            MateriaPrima* temp = raiz->dir;
            free(raiz);
            return temp;
        }
        if (!raiz->dir) {
            MateriaPrima* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        MateriaPrima* temp = menor(raiz->dir);
        raiz->codigo = temp->codigo;
        strcpy(raiz->nome, temp->nome);
        raiz->preco = temp->preco;
        raiz->dir = remover_materia_prima(raiz->dir, temp->codigo);
    }
    return balancear(raiz);
}

void listar_materias_primas(MateriaPrima* raiz) {
    if (!raiz) return;
    listar_materias_primas(raiz->esq);
    printf("Codigo: %d | Nome: %s | Preço: %.2f\n", raiz->codigo, raiz->nome, raiz->preco);
    listar_materias_primas(raiz->dir);
}

void destruir_arvore(MateriaPrima* raiz) {
    if (!raiz) return;
    destruir_arvore(raiz->esq);
    destruir_arvore(raiz->dir);
    free(raiz);
}

// Persistência CSV
MateriaPrima* carregar_materias_csv(const char* nome_arquivo) {
    FILE* arq = fopen(nome_arquivo, "r");
    if (!arq) return NULL;
    MateriaPrima* raiz = NULL;
    int codigo;
    char nome[100];
    float preco;
    while (fscanf(arq, "%d,%99[^,],%f\n", &codigo, nome, &preco) == 3)
        raiz = inserir_materia_prima(raiz, codigo, nome, preco);
    fclose(arq);
    return raiz;
}

void salvar_materias_csv(MateriaPrima* raiz, const char* nome_arquivo) {
    FILE* arq = fopen(nome_arquivo, "w");
    if (!arq) return;
    void salvar(MateriaPrima* n) {
        if (!n) return;
        salvar(n->esq);
        fprintf(arq, "%d,%s,%.2f\n", n->codigo, n->nome, n->preco);
        salvar(n->dir);
    }
    salvar(raiz);
    fclose(arq);
}
