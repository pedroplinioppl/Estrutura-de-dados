#include <stdlib.h>
#include <stdio.h>

typedef struct sNo {
    int val;
    int altura;
    struct sNo *dir;
    struct sNo *esq;
} no;

void inicializar(no **raiz) {
    *raiz = NULL;
}

int altura(no *folha) {
    if (!folha) return 0;
    return folha->altura;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int fatorBalanceamento(no *folha) {
    if (!folha) return 0;
    return altura(folha->esq) - altura(folha->dir);
}

void atualizarAltura(no *folha) {
    if (folha) {
        folha->altura = 1 + max(altura(folha->esq), altura(folha->dir));
    }
}

no *addNo(int val) {
    no *novoNo = malloc(sizeof(no));

    if (!novoNo) return NULL;

    novoNo->val = val;
    novoNo->altura = 1;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

no *rotacaoDireita(no *y) {
    no *x  = y->esq;
    no *B  = x->dir;

    x->dir = y;
    y->esq = B;

    atualizarAltura(y);
    atualizarAltura(x);
    return x;
}

no *rotacaoEsquerda(no *x) {
    no *y  = x->dir;
    no *B  = y->esq;

    y->esq = x;
    x->dir = B;

    atualizarAltura(x);
    atualizarAltura(y);
    return y;
}

no *balancear(no *folha) {
    atualizarAltura(folha);

    int fb = fatorBalanceamento(folha);

    // EE   
    if (fb > 1 && fatorBalanceamento(folha->esq) >= 0)
        return rotacaoDireita(folha);

    // ED   
    if (fb > 1 && fatorBalanceamento(folha->esq) < 0) {
        folha->esq = rotacaoEsquerda(folha->esq);
        return rotacaoDireita(folha);
    }

    // DD   
    if (fb < -1 && fatorBalanceamento(folha->dir) <= 0)
        return rotacaoEsquerda(folha);

    // DE   
    if (fb < -1 && fatorBalanceamento(folha->dir) > 0) {
        folha->dir = rotacaoDireita(folha->dir);
        return rotacaoEsquerda(folha);
    }

    return folha; // já balanceado   
}

no *inserir(no *folha, int val) {
    if (!folha)
        return addNo(val);

    if (val < folha->val) {
        folha->esq = inserir(folha->esq, val);  
    } else if (val > folha->val){
        folha->dir = inserir(folha->dir, val);
    }
        
    return balancear(folha);
}

no *buscar(no *folha, int val) {
    if (folha == NULL || val == folha->val)
        return folha;

    if (val < folha->val){
        return buscar(folha->esq, val);
    } else {
        return buscar(folha->dir, val);
    }
}

no *menorValor(no *folha) {
    if (!folha) return NULL;
    if (!folha->esq) return folha;
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
        // apenas à direita
        if (folha->esq == NULL) {
            no *temp = folha->dir;
            free(folha);
            return temp;
        }
        // apenas à esquerda 
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

    return balancear(folha);
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