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

int inserirFinal(fila *f, int elem) {
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

int inserirInicio(fila *f, int elem) {
    cel *novaCel = adicionarCelula(elem);

    if (!novaCel) {
        return 1;
    }

    if (estaVazia(f)) {
        novaCel->prox = novaCel;
        f->fim = novaCel;
    } else {
        cel * inicio = f->fim->prox;
        novaCel->prox = inicio;
        f->fim->prox = novaCel;

        /*
        inicio é só uma variável local, por isso n da pra fzr inicio = novaCel, isso n alteraria a fila
        masss, daria pra inicio ser um ponteiro pra ponteiro, aí sim daria certo, no caso:
        cel **inicio = &(f->fim->prox);
        novaCel->prox = *inicio;
        *inicio = novaCel;
        Ou novaCel->prox = f->fim->prox; f->fim->prox = novaCel mas ai n tem aura
        */
    }

    return 0;
}

int removerInicio(fila *f) {
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

int removerFinal(fila *f) {
    if (estaVazia(f)) {
        return 1;
    }

    cel *inicio = f->fim->prox;

    if (inicio == f->fim) {
        free(f->fim);
        f->fim = NULL;
    } else {
        cel *atual = inicio;

        while (atual->prox != f->fim) {
            atual = atual->prox;
        }

        cel *fim = f->fim;
        atual->prox = f->fim->prox;
        f->fim = atual;
        free(fim);
    }

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

    inserirFinal(&f, 10);
    inserirInicio(&f, 5);
    inserirFinal(&f, 12);
    inserirInicio(&f, 2);
    
    mostrarFila(f); // 2 5 10 12

    removerInicio(&f);

    removerFinal(&f);

    mostrarFila(f); // 5 10
    
    return 0;
}