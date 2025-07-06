#ifndef PRODUTO_H
#define PRODUTO_H

#include "materia_prima.h"

typedef struct MatProduto {
    int codigo_materia;
    int qtde;
    struct MatProduto *prox, *ant;
} MatProduto;

typedef struct Produto {
    int codigo;
    char nome[100];
    float margemLucro;
    struct Produto *prox, *ant;
    MatProduto *ini_mat;
} Produto;

// CRUD Produto
Produto* inserir_produto(Produto* ini, int codigo, const char* nome, float margemLucro);
Produto* buscar_produto(Produto* ini, int codigo);
Produto* remover_produto(Produto* ini, int codigo);
void alterar_produto(Produto* prod, const char* nome, float margemLucro);
void listar_produtos(Produto* ini, MateriaPrima* raiz);

// CRUD Matéria-Prima em Produto
void adicionar_mat_produto(Produto* prod, int cod_mat, int qtde);
void remover_mat_produto(Produto* prod, int cod_mat);
void alterar_mat_produto(Produto* prod, int cod_mat, int qtde);
void listar_mats_produto(Produto* prod, MateriaPrima* raiz);

// Preço
float calcular_custo_produto(Produto* prod, MateriaPrima* raiz);
void exibir_detalhes_produto(Produto* prod, MateriaPrima* raiz);

void destruir_lista_produtos(Produto* ini);

#endif
