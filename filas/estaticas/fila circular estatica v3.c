#include <stdio.h>

#define MAX 5

/*
    Essa é a versão apresentada pelo zorzan
*/

typedef struct f {
    int arr[MAX];
    int inicio, fim;
} fila;

void inicializar(fila *f) {
    f->inicio = MAX - 1;
    f->fim = MAX - 1;
}

int verificarFila(fila *f) {
    return f->inicio == f->fim;
}

void enqueue(fila *f, int x) {
    f->fim = (f->fim + 1) % MAX;

    if (verificarFila(f)) {
        printf("Erro: fila cheia\n");
        f->fim = (f->fim - 1 + MAX) % MAX;
        // Equivalente a f->fim - 1 == -1 ? f->fim = 0 : f->fim = f-> fim - 1
        return;
    }

    f->arr[f->fim] = x;
}

int dequeue(fila *f) {
    int aux = 0; // serve pra retornar o valor retirado.

    if (!verificarFila(f)) {
        f->inicio = (f->inicio + 1) % MAX;
        aux = f->arr[f->inicio];
    } else {
        printf("Fila vazia\n");
    }

    return aux;
}

void imprimir(fila f) {
    int i = (f.inicio + 1) % MAX;

    if(!verificarFila(&f)) {
        printf("\nFila: ");
        while(i != (f.fim + 1) % MAX) {
            printf("%d ", f.arr[i]);
            i = (i + 1) % MAX;
        } 
    } else {
        printf("Fila vazia\n");
    }
}

int main() {
    fila f;
    inicializar(&f);

    for (int i = 0; i < 5; i++) {
        enqueue(&f, i + 1);
    }

    imprimir(f);   

    for (int i = 0; i < 3; i++) {
        dequeue(&f);
    }

    for (int i = 0; i < 3; i++) {
        enqueue(&f, i + 10);
    }

    imprimir(f); 
}