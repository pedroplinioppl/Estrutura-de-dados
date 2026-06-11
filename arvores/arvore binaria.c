#include <stdlib.h>
#include <stdio.h>

typedef struct sNo {
    int val;
    struct sNo *dir;
    struct sNo *esq;
} no;

void inicializar(no **raiz) {
    *raiz = NULL;
}

no *addNo(int val) {
    no *novoNo = malloc(sizeof(no));
    
    if(!novoNo) {
        return;
    }

    novoNo->val = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}

no * inserir(no *folha, int val) {
    if(!folha) {
        no *novo = addNo(val);
        
        return novo;
    }
    
    if(folha->val > val) 
    {
        folha->esq = inserir(folha->esq, val);
    } 
    else if(folha->val < val) 
    {
        folha->dir = inserir(folha->dir, val);
    } 
    
    return folha;
}

no * busca(no *folha, int val) {
    if(folha == NULL || val == folha->val) {
        return folha;
    }
    
    if(folha->val > val) {
        return busca(folha->esq, val);
    } else {
        return busca(folha->dir, val);
    } 
}

no *menorValor(no *folha) {
    if (!folha) {
        return NULL;
    }

    if (!folha->esq)
        return folha;

    return menorValor(folha->esq);
}

no *remover(no *folha, int val) {

    if (folha == NULL)
        return NULL;

    if (val < folha->val) {
        folha->esq = remover(folha->esq, val);

    } else if (val > folha->val) {
        folha->dir = remover(folha->dir, val);
    } else {

        // sem filhos
        if (folha->esq == NULL && folha->dir == NULL) {

            free(folha);
            return NULL;
        }

        // apenas na direita
        if (folha->esq == NULL) {

            no *temp = folha->dir;
            free(folha);
            return temp;
        }

        // apenas na esquerda
        if (folha->dir == NULL) {

            no *temp = folha->esq;
            free(folha);
            return temp;
        }

        // dois filhos
        no *temp = menorValor(folha->dir);

        folha->val = temp->val;

        folha->dir = remover(folha->dir, temp->val);
    }

    return folha;
}
void preOrdem(no *folha) {
    if (folha) {
        printf("%d ", folha->val);
        preOrdem(folha->esq);
        preOrdem(folha->dir);
    }
}

void emOrdem(no *folha) {
    if (folha) {
        emOrdem(folha->esq);
        printf("%d ", folha->val);
        emOrdem(folha->dir);
    }
}

void posOrdem(no *folha) {
    if (folha) {
        posOrdem(folha->esq);
        posOrdem(folha->dir);
        printf("%d ", folha->val);
    }
}

int main() {
    no *raiz;

    inicializar(&raiz);

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 7);
    
    raiz = remover(raiz, 7);

    emOrdem(raiz);

    return 0;
}