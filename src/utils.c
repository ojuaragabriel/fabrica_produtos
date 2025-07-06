#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void limpar_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_int(const char* msg) {
    int v;
    printf("%s", msg);
    scanf("%d", &v);
    limpar_entrada();
    return v;
}

float ler_float(const char* msg) {
    float v;
    printf("%s", msg);
    scanf("%f", &v);
    limpar_entrada();
    return v;
}

void ler_string(const char* msg, char* buf, int tam) {
    printf("%s", msg);
    fgets(buf, tam, stdin);
    size_t l = strlen(buf);
    if (l > 0 && buf[l-1] == '\n') buf[l-1] = '\0';
}
