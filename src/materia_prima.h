#ifndef MATERIA_PRIMA_H
#define MATERIA_PRIMA_H

typedef struct MateriaPrima {
    int codigo;
    char nome[100];
    float preco;
    struct MateriaPrima *esq, *dir;
} MateriaPrima;

MateriaPrima* inserir_materia_prima(MateriaPrima* raiz, int codigo, const char* nome, float preco);
MateriaPrima* remover_materia_prima(MateriaPrima* raiz, int codigo);
MateriaPrima* buscar_materia_prima(MateriaPrima* raiz, int codigo);
void listar_materias_primas(MateriaPrima* raiz);
void destruir_arvore(MateriaPrima* raiz);
int altura(MateriaPrima* n);
MateriaPrima* balancear(MateriaPrima* raiz);
MateriaPrima* carregar_materias_csv(const char* nome_arquivo);
void salvar_materias_csv(MateriaPrima* raiz, const char* nome_arquivo);

#endif
