#include <stdio.h>

/*
A ideia da lista circular estática é sempre que aumentar ou diminuir, considerar usar módulo pra que o índice sempre esteja no
intervalo da lista, fora isso, não da pra usar uma convenção normal de tamanho pois o início nem sempre é zero
 e nem sempre fim > inicio
*/

#define MAX 5

typedef struct f {
    int arr[MAX];
    int inicio;
    int fim;
} lista;

void inicializar(lista *l) {
    l->inicio = MAX - 1;
    l->fim = MAX - 1;
}

int estaVazia(lista *l) {
    return l->fim == l->inicio;
}

int estaCheia(lista *l) { 
    return (l->fim + 1) % MAX == l->inicio;
}

int tamanho(lista *l) {
    return (l->fim - l->inicio + MAX) % MAX; 
}

int inserirFim(lista *l, int x) {
    if(estaCheia(l)) 
    {
        return 1;
    }
    l->fim = (l->fim + 1) % MAX;
    l->arr[l->fim] = x;

    return 0;
}

int inserirInicio(lista *l, int elem) {
    if(estaCheia(l)) 
    {
        return 1;
    }

    int i = l->fim;
    while(i != (l->inicio - 1 + MAX) % MAX) {
        l->arr[(i + 1) % MAX] = l->arr[i];
        i = (i - 1 + MAX) % MAX;
    }

    l->inicio = (l->inicio - 1 + MAX) % MAX;
    l->arr[(l->inicio + 1) % MAX] = elem;
    l->fim = (l->fim + 1) % MAX;
    return 0;
}

int inserirPos(lista *l, int pos, int elem) {
    if(estaCheia(l) || pos < 0 || pos > tamanho(l)) {
        return 1;
    }

    pos = (l->inicio + 1 + pos) % MAX; // Pos tem que ser ajustado pois o inicio nem sempre é em 0
    int i = l->fim;
    while(i != (pos - 1 + MAX) % MAX) {
        l->arr[(i + 1) % MAX] = l->arr[i];
        i = (i - 1 + MAX) % MAX;
    }
    l->arr[pos] = elem;
    l->fim = (l->fim + 1) % MAX;
    return 0;
}

int removerInicio(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }

    l->inicio = (l->inicio + 1) % MAX; 

    return 0;
}

int removerFim(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }

    l->fim = (l->fim - 1 + MAX) % MAX;

    return 0;
} 

int removerPos(lista *l, int pos) {
    if(estaVazia(l) || pos < 0 || pos >= tamanho(l)) {
        return 1;
    }

    pos = (l->inicio + 1 + pos) % MAX;

    int i = pos;
    while(i != l->fim) {
        int prox = (i + 1) % MAX;
        l->arr[i] = l->arr[prox];
        i = prox;
    }

    l->fim = (l->fim - 1 + MAX) % MAX;

    return 0;
}

void mostrarLista(lista *l) {
    if(estaVazia(l)) {
        return;
    }

    int i = (l->inicio + 1) % MAX;
    int f = tamanho(l); // f é abreviação pra fim nesse caso

    for(int c=0; c<f; c++) {
        printf("%d ", l->arr[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() 
{
    lista l;

    inicializar(&l);
    
    inserirInicio(&l, 10);
    inserirFim(&l, 5);
    inserirPos(&l, 1, 12);
    inserirFim(&l, 56);
    
    removerInicio(&l);
    removerFim(&l);
    removerPos(&l, 1);
    
    // A saída dá 12 

    mostrarLista(&l);

}