#include <stdio.h>

#define MAX 5

typedef struct f {
    int arr[MAX];
    int inicio;
    int fim;
    int qtd;
} fila;

void inicializar(fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

int estaVazia(fila *f) {
    return f->qtd == 0;
}

int estaCheia(fila *f) {
    return f->qtd == MAX;
}

int tamanho(fila *f) {
    return f->qtd;
}

int enqueue(fila *f, int x) {
    if (estaCheia(f)) {
        return 1;
    }

    f->arr[f->fim] = x;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;

    return 0;
}

int dequeue(fila *f) {
    if (estaVazia(f)) {
        return 1;
    }

    f->inicio = (f->inicio + 1) % MAX;
    f->qtd--;

    return 0;
}

void mostrarFila(fila *f) {
    if (estaVazia(f)) {
        printf("Fila vazia\n");
        return;
    }

    int i = f->inicio;

    for (int c = 0; c < f->qtd; c++) {
        printf("%d ", f->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    fila f;
    inicializar(&f);

    for (int i = 0; i < 5; i++) {
        enqueue(&f, i + 1);
    }

    mostrarFila(&f);  

    for (int i = 0; i < 3; i++) {
        dequeue(&f);
    }

    for (int i = 0; i < 3; i++) {
        enqueue(&f, i + 10);
    }

    mostrarFila(&f); 
}