# Diagramas Hierárquicos e Documentação

## Funções Principais

- main
    - menu_principal
        - inserir_produto
        - buscar_produto
        - alterar_produto
        - remover_produto
        - listar_produtos
        - adicionar_mat_produto
        - remover_mat_produto
        - alterar_mat_produto
        - exibir_detalhes_produto
        - inserir_materia_prima
        - buscar_materia_prima
        - remover_materia_prima
        - listar_materias_primas
        - salvar_materias_csv
        - carregar_materias_csv
        - salvar_produtos_csv
        - carregar_produtos_csv

---

## Dados de Entrada

- **Teclado:** códigos, nomes, margens, preços, quantidades.
- **Arquivos CSV:** listas de produtos e matérias-primas.

---

## Dados de Saída

- **Tela:** listagens, confirmações, resultados dos cálculos.
- **Arquivos CSV:** dados persistidos.

---

## O que cada função faz

Consulte os protótipos nos arquivos header (.h) e os comentários presentes no código-fonte para detalhes sobre cada função.

---

# Como Compilar e Executar o Projeto


## Passo a Passo para Rodar o Projeto no VS Code

1. **Abra a pasta do projeto no VS Code**
   - Arquivo > Abrir Pasta... e selecione a pasta `fabrica_produtos`.

2. **Abra o terminal integrado**
   - Atalho Ctrl + ` (crase) ou Terminal > Novo Terminal.

3. **Acesse a pasta `src`**
   - `cd src`

4. **Compile todos os arquivos `.c`**
   - `gcc main.c materia_prima.c persistencia.c produto.c ui.c utils.c -o ../fabrica.exe`
   - Isso gera o executável `fabrica.exe` na pasta principal do projeto.
   - No Linux, use `-o ../fabrica` e rode como `./fabrica`.

5. **Volte para a pasta principal**
   - `cd ..`

6. **Execute o programa**
   - No Windows: `fabrica.exe`
   - No Linux: `./fabrica`

---

## Possíveis Problemas e Soluções

- **GCC não instalado:**  
  `'gcc' não é reconhecido como um comando interno ou externo...`  
  Instale o MinGW no Windows e adicione ao PATH.

- **Erro com arquivos `.h`:**  
  Verifique se todos os headers estão na pasta `src` e se os nomes nos `#include` estão corretos.

- **Permissão no Linux:**  
  Se necessário, rode: `chmod +x fabrica`

- **Erros de compilação:**  
  Verifique a mensagem de erro e confira se não há funções faltando ou nomes digitados incorretamente.

---

## Sobre as Funções do Projeto

Para detalhes sobre o funcionamento de cada função, consulte:  
- Os protótipos nos arquivos header (.h)  
- Os comentários explicativos nos arquivos .c do projeto