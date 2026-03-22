#include <stdio.h>
#include <stdlib.h>

typedef struct sCel {
    int num;
    struct sCel *prox;
} cel;

typedef struct {
    cel *top;
} pilha;

void inicializar(pilha *p) {
    p->top = NULL;
}

int estaVazia(pilha *p) {
    return p->top == NULL;
}

cel * adicionarCel(int num) {
    cel *novaCel = (cel*) malloc(sizeof(cel));

    if(!novaCel) return NULL;

    novaCel->prox = NULL;
    novaCel->num = num;

    return novaCel;
}

int push(pilha *p, int elem) {
    cel *novaCel = adicionarCel(elem);

    if(!novaCel) return 1;

    novaCel->prox = p->top;
    p->top = novaCel;
    
    return 0;
}

int pop(pilha *p) {
    if(estaVazia(p)) return -1;

    cel *top = p->top;
    int n = top->num;

    p->top = top->prox; 
    free(top);

    return n;
}

void mostrarPilha(pilha *p) { // mostra invertido
    cel *atual = p->top;

    while(atual != NULL) {
        printf("%d ", atual->num);
        atual = atual->prox;
    }
    printf("\n");
}

void mostrarPilhaCorreto(pilha *p) { // mostra na ordem do push
    pilha aux;
    inicializar(&aux);

    while(!estaVazia(p)) {
        push(&aux, pop(p));
    }

    while(!estaVazia(&aux)) {
        int val = pop(&aux);
        printf("%d ", val);
        push(p, val);  
    }

    printf("\n");
}


int main() {
    pilha p;
    
    inicializar(&p);

    for(int i=0; i<10; i++) {
        push(&p, i+1);
    }

    mostrarPilha(&p);

    printf("\n");

    mostrarPilhaCorreto(&p);

    return 0;
}