#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "produto.h"
#include "materia_prima.h"

// Produtos
Produto* carregar_produtos_csv(const char* nome_arquivo);
void salvar_produtos_csv(Produto* ini, const char* nome_arquivo);

// Matérias-primas (já definidos em materia_prima.h)
// MateriaPrima* carregar_materias_csv(const char* nome_arquivo);
// void salvar_materias_csv(MateriaPrima* raiz, const char* nome_arquivo);

// Ligação Produto <-> Matérias (carrega lista encadeada MatProduto de um campo CSV)
void carregar_mats_produto(Produto* prod, const char* str);
void salvar_mats_produto(FILE* arq, Produto* prod);

#endif
