#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int arr[MAX];
    int inicio, fim;
} fila;

void inicializar(fila *f) {
    f->inicio = -1;
    f->fim = -1;
}

int estaVazia(fila *f) {
    return f->inicio == -1;
}

int estaCheia(fila *f) {
    return f->fim == MAX - 1;
}

int inserirFinal(fila *f, int elem) {
    if (estaCheia(f)) {
        return 1;
    }

    if (estaVazia(f)) {
        f->inicio = 0;
    }

    f->arr[++f->fim] = elem;
    return 0;
}

int inserirInicio(fila *f, int elem) {
    if (estaCheia(f)) {
        return 1;
    }

    if (estaVazia(f)) {
        f->inicio = 0;
        f->fim = 0;
        f->arr[0] = elem;
        return 0;
    }

    for (int i = f->fim + 1; i > f->inicio; i--) {
        f->arr[i] = f->arr[i - 1];
    }

    f->arr[f->inicio] = elem;
    f->fim++;

    return 0;
}

int removerInicio(fila *f) {
    if (estaVazia(f)) {
        return 1;
    }

    if (f->inicio == f->fim) {
        f->inicio = -1;
        f->fim = -1;
    } else {
        f->inicio++;
    }

    return 0;
}

int removerFinal(fila *f) {
    if (estaVazia(f)) {
        return 1;
    }

    if (f->inicio == f->fim) {
        f->inicio = -1;
        f->fim = -1;
    } else {
        f->fim--;
    }

    return 0;
}

void mostrarFila(fila *f) {
    if (estaVazia(f)) {
        return;
    }

    for (int i = f->inicio; i <= f->fim; i++) {
        printf("%d ", f->arr[i]);
    }

    printf("\n");
}

int main() {
    fila f;
    inicializar(&f);

    inserirFinal(&f, 10);
    inserirFinal(&f, 20);
    inserirInicio(&f, 5);

    mostrarFila(&f);

    removerInicio(&f);
    mostrarFila(&f);

    removerFinal(&f);
    mostrarFila(&f);

    return 0;
}