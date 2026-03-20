#include <stdio.h>
#include <stdlib.h>

/*
A ideia da lista encadeada circular é a célula final apontar pro início.
*/

typedef struct sCel {
    int num;
    struct sCel *prox; 
} cel;

typedef struct {
    cel *fim; // uma lista circular só precisa apontar pro final, pois o começo é logo o próximo
} lista;

void inicializar(lista *l) {
    l->fim = NULL;
}

int estaVazia(lista *l) {
    return l->fim == NULL;
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

int inserirInicio(lista *l, int elem) {
    cel *novaCel = adicionarCelula(elem);
    
    if (!novaCel) {
        return 1;
    }

    if (estaVazia(l)) {
        novaCel->prox = novaCel;
        l->fim = novaCel;
    } else {
        novaCel->prox = l->fim->prox;
        l->fim->prox = novaCel;
    }

    return 0;
}

int inserirFim(lista *l, int elem) {
    cel *novaCel = adicionarCelula(elem);
    
    if(!novaCel) {
        return 1;
    }
    
    if(estaVazia(l)) {
        novaCel->prox = novaCel;
        l->fim = novaCel;
    } else {
        novaCel->prox = l->fim->prox;
        l->fim->prox = novaCel;
        l->fim = novaCel;
    }
    
    return 0;
}

int inserirPos(lista *l, int pos, int elem) {
    cel *novaCel = adicionarCelula(elem);
    
    if (!novaCel || pos < 0) {
        printf("Posicao invalida.\n");
        return 1;
    }

    if (estaVazia(l)) {
        if (pos > 0) {
            printf("Posicao invalida\n");
            return 1;
        }
        novaCel->prox = novaCel;
        l->fim = novaCel;
        return 0;
    }

    cel *atual = l->fim->prox; // começa no início

    if (pos == 0) {
        inserirInicio(l, elem);
        return 0;
    }

    while (pos > 1 && atual != l->fim) { // Para uma posição antes da requisitada
        atual = atual->prox;
        pos--;
    }

    if (pos > 1) {
        printf("Posicao invalida\n");
        return 1;
    }

    novaCel->prox = atual->prox;
    atual->prox = novaCel;

    if (atual == l->fim) {
        l->fim = novaCel;
    }

    return 0;
}

int removerInicio(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }
    
    cel *inicio = l->fim->prox;
    
    if(inicio == l->fim) {
        l->fim = NULL;
    } else {
        l->fim->prox = inicio->prox;
    }
    
    free(inicio);
    return 0;
}

int removerPos(lista *l, int pos) {
    if (estaVazia(l) || pos < 0) {
        printf("Lista vazia ou posicao invalida\n");
        return 1;
    }

    cel *atual = l->fim->prox;  
    cel *prev = l->fim; 

    if (pos == 0) {
        removerInicio(l);
        return 0;
    }

    for (int i = 0; i < pos; i++) {
        prev = atual;
        atual = atual->prox;
        if (atual == l->fim->prox) { //Atual ser igual a inicio implica que a lista toda ja foi investigada
            printf("Posicao invalida\n");
            return 1;
        }
    }

    prev->prox = atual->prox;
    if (atual == l->fim) { 
        l->fim = prev;
    }

    free(atual);
    return 0;
}

int removerFinal(lista *l) {
    if (estaVazia(l)) {
        return 1;  
    }

    cel *inicio = l->fim->prox;
    cel *fim = l->fim;

    if (inicio == l->fim) {  
        free(fim);
        l->fim = NULL;
    } else {
        cel *atual = inicio;

        while (atual->prox != fim) {
            atual = atual->prox;
        }
        atual->prox = inicio;
        free(fim);
        l->fim = atual;
    }

    return 0;
}

void mostrarLista(lista l) {
    if (estaVazia(&l)) {
        printf("Lista vazia\n");
        return;
    }

    cel *inicio = l.fim->prox;
    cel *atual = inicio;

    do {
        printf("%d ", atual->num);
        atual = atual->prox;
    } while (atual != inicio);

    printf("\n");
}

int main() {
    lista l;
    inicializar(&l);
    
    for(int i=0; i<10;i++) {
        inserirPos(&l, i, i+1);
    }
    
    inserirInicio(&l, 20);
    
    inserirFim(&l, 15);
    
    mostrarLista(l);
    
    removerInicio(&l);
    
    removerFinal(&l);
    
    removerPos(&l, 4);
    
    mostrarLista(l);
    
    return 0;
}