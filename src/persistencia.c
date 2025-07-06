#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "materia_prima.h"
#include "persistencia.h"

// Formato CSV produto: codigo,nome,margem,mat1:qtde1;mat2:qtde2;...

Produto* carregar_produtos_csv(const char* nome_arquivo) {
    FILE* arq = fopen(nome_arquivo, "r");
    if (!arq) return NULL;
    Produto* ini = NULL;
    int codigo;
    char nome[100];
    float margem;
    char materias[500];

    while (fscanf(arq, "%d,%99[^,],%f,%499[^\n]\n", &codigo, nome, &margem, materias) == 4) {
        ini = inserir_produto(ini, codigo, nome, margem);
        carregar_mats_produto(ini, materias);
    }
    fclose(arq);
    return ini;
}

void salvar_produtos_csv(Produto* ini, const char* nome_arquivo) {
    FILE* arq = fopen(nome_arquivo, "w");
    if (!arq) return;
    Produto* p = ini;
    while (p) {
        fprintf(arq, "%d,%s,%.2f,", p->codigo, p->nome, p->margemLucro);
        salvar_mats_produto(arq, p);
        fprintf(arq, "\n");
        p = p->prox;
    }
    fclose(arq);
}

// Carrega lista MatProduto a partir de string tipo "1:5;2:3;"
void carregar_mats_produto(Produto* prod, const char* str) {
    int cod, qtde;
    const char* p = str;
    while (sscanf(p, "%d:%d", &cod, &qtde) == 2) {
        adicionar_mat_produto(prod, cod, qtde);
        // Avança até próximo ';'
        p = strchr(p, ';');
        if (!p) break;
        p++; // pula ';'
    }
}

// Salva lista MatProduto no formato "codigo:qtde;codigo:qtde;"
void salvar_mats_produto(FILE* arq, Produto* prod) {
    MatProduto* mp = prod->ini_mat;
    while (mp) {
        fprintf(arq, "%d:%d;", mp->codigo_materia, mp->qtde);
        mp = mp->prox;
    }
}
