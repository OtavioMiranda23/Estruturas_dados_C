#include<stdio.h>
#include<stdlib.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

void print(celula *fst);
celula *find(int x, celula *fst);
int isSorted(celula *fst);
celula *findInSortedList(celula *fst, int x);
celula *findInSortedListR(celula *fst, int x);
int findMinValue(celula *fst);
int isEqualList(celula *frst1, celula *frst2);
celula *middlePoint(celula *c);
int main(int argc, char const *argv[])
{
    celula *lst = malloc(sizeof(celula));
    celula *primeira = malloc(sizeof(celula));
    celula *segunda = malloc(sizeof(celula));
    celula *terceiro = malloc(sizeof(celula));
    primeira->conteudo = 1;
    segunda->conteudo = 2;
    terceiro->conteudo = 3;
    lst->seg = primeira;
    primeira->seg = segunda;
    segunda->seg = terceiro;
    terceiro->seg = NULL;
    printf("%d\n", middlePoint(primeira)->conteudo);
    // Teste 1: Listas Iguais
    // celula *a1 = malloc(sizeof(celula));
    // celula *a2 = malloc(sizeof(celula));
    // celula *a3 = malloc(sizeof(celula));
    // a1->conteudo = 10;
    // a2->conteudo = 20;
    // a3->conteudo = 30;
    // a1->seg = a2;
    // a2->seg = a3;
    // a3->seg = NULL;

    // celula *b1 = malloc(sizeof(celula));
    // celula *b2 = malloc(sizeof(celula));
    // celula *b3 = malloc(sizeof(celula));
    // b1->conteudo = 10;
    // b2->conteudo = 20;
    // b3->conteudo = 30;
    // b1->seg = b2;
    // b2->seg = b3;
    // b3->seg = NULL;

    // printf("Teste 1 (iguais): %d\n", isEqualList(a1, b1)); // Esperado: 1

    // // Teste 2: Listas Diferentes
    // b2->conteudo = 99; // Muda um valor

    // printf("Teste 2 (diferentes): %d\n", isEqualList(a1, b1)); // Esperado: 0
    return 0;
}

//Lista com cabeça: a primeira serve marca o início, seu conteúdo é irrelevante
void print(celula *fst) {
    celula *p;
    for (p = fst; p != NULL; p = p->seg) {
        printf("%d\n", p->conteudo);
    }
}

celula *find(int x, celula *fst) {
    celula *p;
    p = fst->seg;
    while (p != NULL && p->conteudo != x) {
        p = p->seg;
    }
    return p;
}

void removeCel(celula *p) { //recebe o elemento anterior ao desejado
    celula *lixo;
    lixo = p->seg; //selecionado o atual + 1
    p->seg = lixo->seg; //coloca no endereço do atual, o atual + 2
    free(lixo); //exclui o atual mais + 1
}

int isSorted(celula *fst) {
    celula *c;
    c = fst;
    for(c = fst; c->seg != NULL || c->conteudo > c->seg->conteudo; c = c->seg) return 0;
    return 1;
}

//Escreva uma função que faça uma busca em uma lista encadeada crescente. Faça versões recursiva e iterativa.
celula *findInSortedList(celula *fst, int x) {
    celula *c;
    c = fst;
    while (c->seg != NULL && c->conteudo != x) {
        c = c->seg;
    }
    return c;
}

celula *findInSortedListR(celula *fst, int x) {
    if (fst == NULL) return NULL;
    if (fst->conteudo == x) return fst;
    return findInSortedListR(fst->seg, x); 
}

//Escreva uma função que encontre uma célula com conteúdo mínimo
int findMinValue(celula *fst) {
    celula *c;
    c = fst;
    int acc;
    acc = fst->conteudo;
    while (c->seg != NULL) {
        if (c->conteudo < acc) acc = c->conteudo;
        c = c->seg;
    }
    return acc;
}

//Escreva uma função que verifique se duas listas encadeadas são iguais, ou melhor, se têm o mesmo conteúdo
int isEqualList(celula *frst1, celula *frst2) {
    while (frst1 != NULL && frst2 != NULL) {
        if (frst1->conteudo != frst2->conteudo) return 0;
        frst1 = frst1->seg;
        frst2 = frst2->seg;
    }
    return frst1 == NULL && frst2 == NULL; 
}


//Escreva uma função que receba uma lista encadeada e devolva o endereço de uma célula que esteja o mais próximo possível do meio da lista
celula *middlePoint(celula *c) {
    celula *p = c;
    int count = 0;
    while (c != NULL) {
        count++;
        c = c->seg;
    }
    int middle = count/2;
    while (middle--) {
        p = p->seg;
    }
    return p;
}