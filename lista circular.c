#include <stdio.h>

#define TAMMAX 5

typedef struct f {
    int arr[TAMMAX];
    int inicio;
    int fim;
} lista;

void inicializar(lista *l) {
    l->inicio = TAMMAX - 1;
    l->fim = TAMMAX - 1;
}

int estaVazia(lista *l) {
    return l->fim == l->inicio;
}

int estaCheia(lista *l) { 
    return (l->fim + 1) % TAMMAX == l->inicio;
}

int inserirFim(lista *l, int x) {
    if(estaCheia(l)) 
    {
        printf("/nERRO: lista cheia. \n");
        return 1;
    }
    l->fim = ((*l).fim + 1) % TAMMAX;
    l->arr[l->fim] = x;

    return 0;
}

int inserirInicio(lista *l, int x) {
    if(estaCheia(l)) 
    {
        printf("Nao da nao pae");
        return 1;
    }

    int i = l->fim;
    while(i != (l->inicio - 1 + TAMMAX) % TAMMAX) {
        l->arr[(i + 1) % TAMMAX] = l->arr[i];
        i = (i - 1 + TAMMAX) % TAMMAX;
    }

    l->arr[l->inicio] = x;
    l->fim = (l->fim + 1) % TAMMAX;
    return 0;
}

int removerInicio(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }

    l->inicio = (l->inicio + 1) % TAMMAX; 

    return 0;
}

void imprimir(lista *l) {
    int i = (l->inicio + 1) % TAMMAX;
    if(!vazia(l)) {
        printf("\nFila: ");
        while(i != ((l->fim + 1) % TAMMAX)) {
            printf("%d ", l->arr[i]);
            i = (i + 1) % TAMMAX;
        }
    } else {
        printf("\nFila vazia");
    }
    printf("\n");
}

int main() 
{
    lista l;

    inicializar(&l);

}
    
