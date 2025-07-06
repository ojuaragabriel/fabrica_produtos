#include <stdio.h>
#include "ui.h"
#include "utils.h"
#include "produto.h"
#include "materia_prima.h"
#include "persistencia.h"

void menu_principal(Produto** lista, MateriaPrima** raiz, const char* arq_prod, const char* arq_mat) {
    int op;
    do {
        printf("\n==== MENU ====\n");
        printf("1. Inserir produto\n");
        printf("2. Alterar produto\n");
        printf("3. Excluir produto\n");
        printf("4. Listar produtos\n");
        printf("5. Calcular/Exibir produto\n");
        printf("6. Inserir materia-prima\n");
        printf("7. Alterar materia-prima\n");
        printf("8. Excluir materia-prima\n");
        printf("9. Listar materias-primas\n");
        printf("0. Salvar e sair\n");
        op = ler_int("Escolha: ");

        int cod, qtde;
        char nome[100];
        float margem, preco;
        Produto* prod = NULL;
        MateriaPrima* mat = NULL;
        switch(op) {
        case 1:
            cod = ler_int("Codigo produto: ");
            ler_string("Nome: ", nome, 100);
            margem = ler_float("Margem de lucro (%%): ");
            *lista = inserir_produto(*lista, cod, nome, margem);
            printf("Deseja adicionar materias-primas? (1=Sim, 0=Nao)");
            if (ler_int("") == 1) {
                do {
                    cod = ler_int("Codigo matéria: ");
                    qtde = ler_int("Qtde: ");
                    adicionar_mat_produto(*lista, cod, qtde);
                    printf("Mais uma? (1=Sim, 0=Nao) ");
                } while (ler_int("") == 1);
            }
            printf("Confirma salvar? (1=Sim, 0=Nao) ");
            if (ler_int("") == 1)
                salvar_produtos_csv(*lista, arq_prod);
            break;
        case 2:
            cod = ler_int("Codigo produto: ");
            prod = buscar_produto(*lista, cod);
            if (prod) {
                ler_string("Novo nome: ", nome, 100);
                margem = ler_float("Nova margem: ");
                alterar_produto(prod, nome, margem);
                printf("Alterar materias-primas? (1=Sim, 0=Nao)");
                if (ler_int("") == 1) {
                    printf("1-Adicionar 2-Remover 3-Alterar Qtde 0-Sair\n");
                    int mop;
                    do {
                        mop = ler_int("Escolha: ");
                        if (mop == 1) {
                            cod = ler_int("Codigo mat: "); qtde = ler_int("Qtde: ");
                            adicionar_mat_produto(prod, cod, qtde);
                        } else if (mop == 2) {
                            cod = ler_int("Codigo mat: ");
                            remover_mat_produto(prod, cod);
                        } else if (mop == 3) {
                            cod = ler_int("Codigo mat: "); qtde = ler_int("Qtde: ");
                            alterar_mat_produto(prod, cod, qtde);
                        }
                    } while (mop != 0);
                }
                printf("Confirma salvar? (1=Sim, 0=Nao) ");
                if (ler_int("") == 1)
                    salvar_produtos_csv(*lista, arq_prod);
            }
            else printf("Produto nao encontrado!\n");
            break;
        case 3:
            cod = ler_int("Codigo produto: ");
            *lista = remover_produto(*lista, cod);
            printf("Confirma salvar? (1=Sim, 0=Nao) ");
            if (ler_int("") == 1)
                salvar_produtos_csv(*lista, arq_prod);
            break;
        case 4:
            listar_produtos(*lista, *raiz);
            break;
        case 5:
            cod = ler_int("Codigo produto: ");
            prod = buscar_produto(*lista, cod);
            if (prod) exibir_detalhes_produto(prod, *raiz);
            else printf("Produto nao encontrado!\n");
            break;
        case 6:
            cod = ler_int("Codigo mataria: ");
            ler_string("Nome: ", nome, 100);
            preco = ler_float("Preco: ");
            *raiz = inserir_materia_prima(*raiz, cod, nome, preco);
            printf("Confirma salvar? (1=Sim, 0=Nao) ");
            if (ler_int("") == 1)
                salvar_materias_csv(*raiz, arq_mat);
            break;
        case 7:
            cod = ler_int("Codigo materia: ");
            mat = buscar_materia_prima(*raiz, cod);
            if (mat) {
                ler_string("Novo nome: ", nome, 100);
                preco = ler_float("Novo preco: ");
                strcpy(mat->nome, nome);
                mat->preco = preco;
                printf("Confirma salvar? (1=Sim, 0=Não) ");
                if (ler_int("") == 1)
                    salvar_materias_csv(*raiz, arq_mat);
            } else printf("Materia-prima nao encontrada!\n");
            break;
        case 8:
            cod = ler_int("Codigo materia: ");
            *raiz = remover_materia_prima(*raiz, cod);
            printf("Confirma salvar? (1=Sim, 0=Nao) ");
            if (ler_int("") == 1)
                salvar_materias_csv(*raiz, arq_mat);
            break;
        case 9:
            listar_materias_primas(*raiz);
            break;
        }
    } while (op != 0);
}
