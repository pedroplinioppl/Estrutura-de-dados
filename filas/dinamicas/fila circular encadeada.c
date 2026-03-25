#include <stdio.h>
#include <stdlib.h>

/*
A ideia da fila encadeada circular é a célula final apontar pro início.
*/

typedef struct sCel {
    int num;
    struct sCel *prox; 
} cel;

typedef struct {
    cel *fim; // uma fila circular só precisa apontar pro final, pois o começo é logo o próximo
} fila;

void inicializar(fila *f) {
    f->fim = NULL;
}

int estaVazia(fila *f) {
    return f->fim == NULL;
}

cel *adicionarCelula(int num) {
    cel *novaCel = (cel*) malloc(sizeof(cel));
    
    if (!novaCel) 
    { 
        return NULL;
    }
    
    novaCel->prox = NULL;
    novaCel->num = num;
    return novaCel;
}

int enqueue(fila *f, int elem) {
    cel *novaCel = adicionarCelula(elem);
    
    if(!novaCel) {
        return 1;
    }
    
    if(estaVazia(f)) {
        novaCel->prox = novaCel;
        f->fim = novaCel;
    } else {
        novaCel->prox = f->fim->prox;
        f->fim->prox = novaCel;
        f->fim = novaCel;
    }
    
    return 0;
}

int dequeue(fila *f) {
    if(estaVazia(f)) {
        return 1;
    }
    
    cel *inicio = f->fim->prox;
    
    if(inicio == f->fim) {
        f->fim = NULL;
    } else {
        f->fim->prox = inicio->prox;
    }
    
    free(inicio);
    return 0;
}

void mostrarFila(fila f) {
    if (estaVazia(&f)) {
        printf("fila vazia\n");
        return;
    }

    cel *inicio = f.fim->prox;
    cel *atual = inicio;

    do {
        printf("%d ", atual->num);
        atual = atual->prox;
    } while (atual != inicio);

    printf("\n");
}

int main() {
    fila f;
    inicializar(&f);

    for(int i=0; i<10; i++) {
        enqueue(&f, i+1);
    }
    
    mostrarFila(f);  

    for (int i = 0; i < 3; i++) {
        dequeue(&f);
    }

    for (int i = 0; i < 3; i++) {
        enqueue(&f, i * 10);
    }

    mostrarFila(f); 
    
    return 0;
}