#include <stdio.h>
#include <stdlib.h>

// Estrutura da célula ('elemento' da lista)
typedef struct sCel {
    int num;
    struct sCel *prox;
    struct sCel *ant; // A diferença da dupla pra simples é a célula 'prev'
} cel; 

// Estrutura que aponta pro início da lista
typedef struct {
    cel *inicio;
    cel *fim; // Não necessário em encadeada dupla, mas sinergiza bem com preview
} lista;

void inicializar(lista *l) {
    l->inicio = NULL;
    l->fim = NULL;
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
    novaCel->ant = NULL;
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

    if(!novaCelula) {
        return 1;
    }


    if(estaVazia(l)) {
        if(pos != 0) { // Posição inválida
            free(novaCelula);
            return 1;
        }

        l->inicio = l->fim = novaCelula;
        return 0;
    }

    cel *atual = l->inicio;

    while(atual != NULL && pos > 0) {
        atual = atual->prox;
        pos--;
    }

    if(pos > 0) {
        free(novaCelula);
        return 1;
    }

    if(atual == l->inicio) { 
        novaCelula->prox = atual;
        atual->ant = novaCelula;
        l->inicio = novaCelula;
        return 0;
    }

    if(atual == NULL) { // parou no último elemento
        novaCelula->ant = l->fim;
        l->fim->prox = novaCelula;
        l->fim = novaCelula;
        return 0;
    }

    novaCelula->prox = atual;
    novaCelula->ant = atual->ant;
    atual->ant->prox = novaCelula;
    atual->ant = novaCelula;

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
        l->fim = novaCelula;
    } else {
        novaCelula->ant = l->fim;
        l->fim->prox = novaCelula;  
        l->fim = novaCelula;
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
        l->fim = novaCelula;
    } else {
        novaCelula->prox = l->inicio;
        l->inicio->ant = novaCelula;
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
    l->inicio->ant = NULL;
    free(inicio);

    return 0;
}

int removerPos(lista *l, int pos) {
    if(estaVazia(l) || pos < 0) {
        return 1;
    }

    cel *atual = l->inicio;

    while(atual != NULL && pos > 0) {
        atual = atual->prox;
        pos--;
    }

    if(atual == NULL) {
        return 1;
    }

    if(atual == l->inicio) {
        l->inicio = atual->prox;
        if(l->inicio != NULL)
            l->inicio->ant = NULL;
        else
            l->fim = NULL; 
    }
    else if(atual == l->fim) {
        l->fim = atual->ant;
        l->fim->prox = NULL;
    }
    else {
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    }

    free(atual);
    return 0;
}

int removerFinal(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }

    cel *remover = l->fim;

    if(l->inicio == l->fim) {
        l->inicio = NULL;
        l->fim = NULL;
    } else {
        l->fim = remover->ant;
        l->fim->prox = NULL;
    }

    free(remover);
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