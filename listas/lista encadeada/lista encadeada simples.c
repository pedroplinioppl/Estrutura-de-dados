#include <stdio.h>
#include <stdlib.h>

// Estrutura da célula ('elemento' da lista)
typedef struct sCel {
    int num;
    struct sCel *next;
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
    novaCel->next = NULL;
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

    cel **temp = &l->inicio;

    while(*temp != NULL && pos > 0) {
        temp = &(*temp)->next;
        pos--;
    }


    // Se a posição não for exatamente 1, a posição requisitada não tava na lista
    if(pos > 0) {
        free(novaCelula);
        return 1;
    }

    novaCelula->next = *temp;
    *temp = novaCelula;

    /*
        Tem outro jeito de fazer a inserção, sem usar ponteiro
        pra ponteiro. Entretanto esse modo é meio gambiarra,
        tu teria que parar uma posição antes do elemento realmente
        requisitado e mudar o next ao invés do propriamente dito elemento
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
        cel *temp = l->inicio;
        
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novaCelula;
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
        novaCelula->next = l->inicio;
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
    l->inicio = l->inicio->next;
    free(inicio);

    return 0;
}

int removerPos(lista *l, int pos) {
    if(estaVazia(l)) {
        return 1;
    }

    cel **temp = &(l->inicio);

    while( *temp != NULL && pos > 1) {
        temp = &((*temp)->next);
        pos--;
    }

    if(*temp == NULL) { // Chegou no final na lista, mas não na posição requisitada.
        return 1;
    }

    cel *elem = *temp;
    *temp = elem->next; // O elemento requisitado vira o próximo
    free(elem);
    return 0;
}

int removerFinal(lista *l) {
    if(estaVazia(l)) {
        return 1;
    }

    cel **temp = &(l->inicio);

    while ( (*temp)->next != NULL ) {
        temp = &((*temp)->next);
    }

    free(*temp);
    *temp = NULL;

    return 0;
}

void mostrarLista(lista l) {
    cel *temp = l.inicio;

    while(temp != NULL) {
        printf("%d ", temp->num);
        temp = temp->next;
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