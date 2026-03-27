#include <stdio.h>

#define MAX 5

/*
    Essa é a versão sem a utilização do campo 'qtd', sempre reserva um espaço (No caso inicio = fim)
    pra diferenciar se ta cheia ou se vazia.
*/

typedef struct f {
    int arr[MAX];
    int inicio;
    int fim;
} fila;

void inicializar(fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

int estaVazia(fila *f) {
    return f->inicio == f->fim;
}

int estaCheia(fila *f) {
    return (f->fim + 1) % MAX == f->inicio;
}

int enqueue(fila *f, int x) {
    if (estaCheia(f)) {
        return 1;
    }

    f->arr[f->fim] = x;
    f->fim = (f->fim + 1) % MAX;

    return 0;
}

int dequeue(fila *f) {
    if (estaVazia(f)) {
        return 1;
    }

    f->inicio = (f->inicio + 1) % MAX;

    return 0;
}

void mostrarFila(fila *f) {
    if (estaVazia(f)) {
        printf("Fila vazia\n");
        return;
    }

    int i = f->inicio;

    while (i != f->fim) {
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