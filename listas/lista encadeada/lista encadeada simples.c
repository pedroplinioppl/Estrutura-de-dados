#include <stdio.h>
#include <stdlib.h>

// Estrutura da célula ('elemento' da lista)
typedef struct sCel {
    int num;
    struct sCel *prox;
} cel; 

// Estrutura que aponta pro início da lista
typedef struct {
    cel *inicio;
} lista;

void inicializar(lista *l) {
    l->inicio = NULL;
}

int estaVazia(lista *l) {
    return l->inicio == NULL;
}

/* Não existe um "estaCheia", pois o limite é até onde a tua 
memória aguenta, entretanto, se você tentar alocar uma cel
e ela retornar NULL (= if(!novaCel)), significa que a memória
está cheia.
*/

// Aloca memória pra uma célula & adiciona um valor a ela
cel * adicionarCel(int num) 
{
    cel * novaCel = (cel*) malloc(sizeof(cel));
    novaCel->prox = NULL;
    novaCel->num = num;
    return novaCel;
}

/* 
    ESTRUTURAS DE INSERÇÃO
*/

//Insere o elemento em uma posição requisitada
int inserirPos(lista *l, int pos, int elem) 
{
    if(pos < 0) {
        return 1;
    }

    cel *novaCelula = adicionarCel(elem);

    cel **atual = &l->inicio;

    while(*atual != NULL && pos > 0) {
        atual = &(*atual)->prox;
        pos--;
    }


    // Se a posição não for exatamente 1, a posição requisitada não tava na lista
    if(pos > 0) {
        free(novaCelula);
        return 1;
    }

    novaCelula->prox = *atual;
    *atual = novaCelula;

    /*
        Tem outro jeito de fazer a inserção, sem usar ponteiro
        pra ponteiro. Entretanto esse modo é meio 'gambiarra',
        tu teria que parar uma posição antes do elemento realmente
        requisitado e mudar o prox ao invés do propriamente dito elemento
    */
    
    return 0;
}

//Insere no final urrr
int inserirFinal(lista *l, int elem) 
{
    cel *novaCelula = adicionarCel(elem);
    if(!novaCelula) {
        return 1;
    }

    if(estaVazia(l)) {
        l->inicio = novaCelula;
    } else {
        cel *atual = l->inicio;
        
        while(atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novaCelula;
    }
    return 0;
}

//...
int inserirInicio(lista *l, int elem) {
    cel *novaCelula = adicionarCel(elem);

    if(!novaCelula) {
        return 1;
    }

    if(estaVazia(l)) {
        l->inicio = novaCelula;
    } else {
        novaCelula->prox = l->inicio;
        l->inicio = novaCelula;
    }

    return 0;
}

/*
    ESTRUTURA DE REMOÇÃO
*/

int removerInicio(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }

    cel *inicio = l->inicio;
    l->inicio = l->inicio->prox;
    free(inicio);

    return 0;
}

int removerPos(lista *l, int pos) {
    if(estaVazia(l)) {
        return 1;
    }

    cel **atual = &(l->inicio);

    while( *atual != NULL && pos > 1) {
        atual = &((*atual)->prox);
        pos--;
    }

    if(*atual == NULL) { // Chegou no final na lista, mas não na posição requisitada.
        return 1;
    }

    cel *elem = *atual;
    *atual = elem->prox; // O elemento requisitado vira o próximo
    free(elem);
    return 0;
}

int removerFinal(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }

    cel **atual = &(l->inicio);

    while ( (*atual)->prox != NULL ) {
        atual = &((*atual)->prox);
    }

    free(*atual);
    *atual = NULL;

    return 0;
}

void mostrarLista(lista l) {
    cel *atual = l.inicio;

    while(atual != NULL) {
        printf("%d ", atual->num);
        atual = atual->prox;
    }

    printf("\n");
}

int main () {
    lista l;
    inicializar(&l);

    for(int i=0; i<10; i++) {
        inserirPos(&l, i, i+1);
    }
    
    inserirInicio(&l, 20);
    inserirFinal(&l, 1);
    

    mostrarLista(l);
    
    removerInicio(&l);
    
    removerFinal(&l);
    
    removerPos(&l, 4);
    
    mostrarLista(l);
}