#include <stdlib.h>
#include <stdio.h>

#define MAX 20

typedef struct {
    int arr[MAX];
    int tam;
} lista; 

// Inicia a lista colocando tamanho = 0 (Daria pra fazer com -1 também)
void inicializar(lista *l) {
    l->tam = 0;
}

int estaCheia(lista *l) {
    return l->tam == MAX-1;
}

int estaVazia(lista *l) {
    return l->tam == 0;
}

// Insere um novo elemento na lista
int inserir(lista *l, int pos, int elem) {
    // Verifica se esta cheio ou se está em posição inválida
    if(estaCheia(l) || pos < 0 || pos > l->tam) {
        return 1;
    }

    // Desloca os elementos pra direita da posição requisitada
    for(int i=l->tam+1; i>pos; i--) {
        l->arr[i] = l->arr[i-1];
    }
    l->arr[pos] = elem;
    l->tam++;
    return 0;
}

// Remove uma posição da lista
int remover(lista *l, int pos) {
    if(estaVazia(l) || pos < 0 || pos >= l->tam) {
        return 1;
    }
    
    // 'Retira' o elemento em pos da lista
    for(int i=pos; i<l->tam; i++) {
        l->arr[i] = l->arr[i+1];
    }

    l->tam--;
    return 0;
}

void mostrarLista(lista l) {
    for(int i=0; i<l.tam; i++) {
        printf("%d ", l.arr[i]);
    }
    printf("\n");
}

int main() {
    lista l;

    inicializar(&l);

    for(int i=0; i<21; i++) {
        inserir(&l, i, i+1);
    }

    for(int i=0; i<4; i++) {
        remover(&l, i);
    }

    mostrarLista(l);

    return 0;
}