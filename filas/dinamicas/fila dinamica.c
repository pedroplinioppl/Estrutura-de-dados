#include <stdlib.h>
#include <stdio.h>

typedef struct sCel {
    int num;
    struct sCel *prox;
} cel; 

typedef struct {
    cel *inicio;
    cel *topo;
} fila;

void inicializar(fila *f) {
    f->inicio = NULL;
    f->topo = NULL;
}

int estaVazia(fila *f) {
    return f->inicio == NULL;
}

cel * addCel(int num) {
    cel * novaCel = (cel*) malloc(sizeof(cel));
    novaCel->prox = NULL;
    novaCel->num = num;

    return novaCel;
}

int enqueue(fila *f, int elem) {
    cel *novaCel = addCel(elem);
    if(!novaCel) {
        return 1;
    }
    if(estaVazia(f)) {
        f->inicio = novaCel;
        f->topo = novaCel;
    } else {
        f->topo->prox = novaCel;
        f->topo = novaCel;
    }

    return 0;
}

int dequeue(fila *f) {
    if(estaVazia(f)) {
        return 1;
    }
    cel * inicio = f->inicio;
    
    if(f->inicio == f->topo) {
        f->topo = NULL;
        f->inicio = NULL;
    } else { 
        f->inicio = inicio->prox;
        
    }

    free(inicio);

    return 0;
}

void mostrarFila(fila f) {
    if(estaVazia(&f)) {
        return;
    }

    cel *atual = f.inicio;

    while(atual != NULL) {
        printf("%d ", atual->num);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    fila f;

    inicializar(&f);

    for(int i=0; i<10; i++) {
        enqueue(&f, i+1);
    }

    mostrarFila(f);
    
    dequeue(&f);
    
    dequeue(&f);
    
    mostrarFila(f);

    return 0;
}