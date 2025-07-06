#include <stdio.h>
#include "produto.h"
#include "materia_prima.h"
#include "persistencia.h"
#include "ui.h"

int main() {
    Produto* lista_prod = carregar_produtos_csv("produtos.csv");
    MateriaPrima* raiz_mat = carregar_materias_csv("materias_primas.csv");

    menu_principal(&lista_prod, &raiz_mat, "produtos.csv", "materias_primas.csv");

    destruir_lista_produtos(lista_prod);
    destruir_arvore(raiz_mat);

    printf("Programa encerrado!\n");
    return 0;
}
