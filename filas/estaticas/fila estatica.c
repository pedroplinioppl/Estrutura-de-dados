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

int enqueue(fila *f, int elem) {
    if (estaCheia(f)) {
        return 1;
    }

    if (estaVazia(f)) {
        f->inicio = 0;
    }

    f->arr[++f->fim] = elem;
    return 0;
}

int dequeue(fila *f) {
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

void mostrarFila(fila f) {
    if(estaVazia(&f)) {
        return;
    }

    for(int i=f.inicio; i<f.fim; i++) {
        printf("%d" , f.arr[i]);
    }

    printf("\n");
}

int main ()
{
    fila f;

    inicializar(&f);

    for(int i=0; i<10; i++) {
        enqueue(&f);
    }

    mostrarFila(f);

    dequeue(&f);

    dequeue(&f);

    mostrarFila(f);

    return 0;
}