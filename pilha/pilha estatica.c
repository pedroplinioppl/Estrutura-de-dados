#include <stdio.h>

#define MAX 10

typedef struct {
    int arr[MAX];
    int top;
} pilha;

void inicializar(pilha *p) {
    p->top = -1;
}

int estaVazia(pilha *p) {
    return p->top == -1;
}

int estaCheia(pilha *p) {
    return p->top == MAX - 1;
}

int push(pilha *p, int elem) {
    if (estaCheia(p)) {
        return 1;
    }

    p->arr[++p->top] = elem;
    return 0;
}

int pop(pilha *p) { //Diferente de um retorno normal de inserção/remoção, pilha retorna o elemento removido
    if(estaVazia(p)) {
        return -1; // -1 sinaliza nenhum elemento removido
    }
    
    int ultimoElemento = p->arr[p->top];
    p->top--;
    return ultimoElemento;
}

int peek(pilha *p) {
    return p->arr[p->top];
}

void mostrarPilha(pilha p) { 
    if(estaVazia(&p)) {
        return;
    }

    for(int i=0; i<p.top+1; i++) {
        printf("%d ", p.arr[i]);
    }
    printf("\n");
}
/* Nunca faça essa função numa prova, eu só to usando ela pra verificar se ta certo as funções
de push e pop
*/


// Esse é o jeito obecendo as regras
void mostrarPilhaCorreto(pilha p) {  // p ao invés de *p é pra não alterar a pilha principal
    pilha aux;
    inicializar(&aux);

    int valor;

    while (!estaVazia(&p)) { // Transfere os valores pra pilha auxiliar
        valor = pop(&p);
        push(&aux, valor);
    }

    while (!estaVazia(&aux)) { // Mostra os valores da pilha auxiliar
        valor = pop(&aux);
        printf("%d ", valor);
    }
    /* A pilha auxiliar é necessária pra manter a ordem, se só mostrasse o pop do original, ia ficar invertido,
    Mas como da pop no auxiliar, vc inverte o q ta invertido e volta pro normal
    */

    printf("\n");
}


int main () {
    pilha p;
    inicializar(&p);

    for(int i=0; i<MAX; i++) {
        push(&p, i+1);
    }

    for(int i=0; i<5; i++) {
        pop(&p);
    }

    mostrarPilhaCorreto(p);
    return 0;
}