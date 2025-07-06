#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "materia_prima.h"

// --- CRUD Produto ---
Produto* inserir_produto(Produto* ini, int codigo, const char* nome, float margemLucro) {
    Produto* novo = malloc(sizeof(Produto));
    novo->codigo = codigo;
    strcpy(novo->nome, nome);
    novo->margemLucro = margemLucro;
    novo->ini_mat = NULL;
    novo->prox = ini;
    novo->ant = NULL;
    if (ini) ini->ant = novo;
    return novo;
}

Produto* buscar_produto(Produto* ini, int codigo) {
    while (ini) {
        if (ini->codigo == codigo) return ini;
        ini = ini->prox;
    }
    return NULL;
}

Produto* remover_produto(Produto* ini, int codigo) {
    Produto* p = ini;
    while (p) {
        if (p->codigo == codigo) {
            if (p->ant) p->ant->prox = p->prox;
            if (p->prox) p->prox->ant = p->ant;
            if (p == ini) ini = p->prox;
            MatProduto* mp = p->ini_mat;
            while (mp) {
                MatProduto* aux = mp;
                mp = mp->prox;
                free(aux);
            }
            free(p);
            return ini;
        }
        p = p->prox;
    }
    return ini;
}

void alterar_produto(Produto* prod, const char* nome, float margemLucro) {
    strcpy(prod->nome, nome);
    prod->margemLucro = margemLucro;
}

// --- CRUD MatProduto (matérias em produto) ---
void adicionar_mat_produto(Produto* prod, int cod_mat, int qtde) {
    MatProduto* mp = prod->ini_mat;
    while (mp) {
        if (mp->codigo_materia == cod_mat) {
            mp->qtde = qtde;
            return;
        }
        mp = mp->prox;
    }
    MatProduto* novo = malloc(sizeof(MatProduto));
    novo->codigo_materia = cod_mat;
    novo->qtde = qtde;
    novo->prox = prod->ini_mat;
    novo->ant = NULL;
    if (prod->ini_mat) prod->ini_mat->ant = novo;
    prod->ini_mat = novo;
}

void remover_mat_produto(Produto* prod, int cod_mat) {
    MatProduto* mp = prod->ini_mat;
    while (mp) {
        if (mp->codigo_materia == cod_mat) {
            if (mp->ant) mp->ant->prox = mp->prox;
            if (mp->prox) mp->prox->ant = mp->ant;
            if (mp == prod->ini_mat) prod->ini_mat = mp->prox;
            free(mp);
            return;
        }
        mp = mp->prox;
    }
}

void alterar_mat_produto(Produto* prod, int cod_mat, int qtde) {
    MatProduto* mp = prod->ini_mat;
    while (mp) {
        if (mp->codigo_materia == cod_mat) {
            mp->qtde = qtde;
            return;
        }
        mp = mp->prox;
    }
}

// --- Listagens ---
void listar_produtos(Produto* ini, MateriaPrima* raiz) {
    Produto* p = ini;
    printf("\n--- Lista de Produtos ---\n");
    while (p) {
        printf("Codigo: %d | Nome: %s | Margem Lucro: %.2f%%\n", p->codigo, p->nome, p->margemLucro);
        listar_mats_produto(p, raiz);
        printf("Custo total: %.2f | Preço de venda: %.2f\n",
            calcular_custo_produto(p, raiz),
            calcular_custo_produto(p, raiz) * (1 + p->margemLucro/100));
        printf("------\n");
        p = p->prox;
    }
}

void listar_mats_produto(Produto* prod, MateriaPrima* raiz) {
    MatProduto* mp = prod->ini_mat;
    printf("  Matérias-primas:\n");
    while (mp) {
        MateriaPrima* mat = buscar_materia_prima(raiz, mp->codigo_materia);
        if (mat)
            printf("    Codigo: %d | Nome: %s | Qtde: %d | Preço un.: %.2f | Custo: %.2f\n",
                mat->codigo, mat->nome, mp->qtde, mat->preco, mp->qtde * mat->preco);
        else
            printf("    Codigo: %d | (não encontrada)\n", mp->codigo_materia);
        mp = mp->prox;
    }
}

// --- Cálculo de custo e preço ---
float calcular_custo_produto(Produto* prod, MateriaPrima* raiz) {
    float total = 0;
    MatProduto* mp = prod->ini_mat;
    while (mp) {
        MateriaPrima* mat = buscar_materia_prima(raiz, mp->codigo_materia);
        if (mat) total += mp->qtde * mat->preco;
        mp = mp->prox;
    }
    return total;
}

void exibir_detalhes_produto(Produto* prod, MateriaPrima* raiz) {
    printf("Codigo: %d | Nome: %s | Margem Lucro: %.2f%%\n", prod->codigo, prod->nome, prod->margemLucro);
    listar_mats_produto(prod, raiz);
    float custo = calcular_custo_produto(prod, raiz);
    printf("Custo total: %.2f\n", custo);
    printf("Preço de venda: %.2f\n", custo * (1 + prod->margemLucro/100));
}

void destruir_lista_produtos(Produto* ini) {
    while (ini) {
        Produto* aux = ini;
        ini = ini->prox;
        MatProduto* mp = aux->ini_mat;
        while (mp) {
            MatProduto* maux = mp;
            mp = mp->prox;
            free(maux);
        }
        free(aux);
    }
}
