#include <stdio.h>
#include <stdlib.h>

//O módulo deve conter as funções  criapilha,  empilha,  desempilha,  pilhavazia,  pilhacheia.
#define MAX_SIZE 100

typedef struct {
    char content[MAX_SIZE];
    int top;
} Stack;

void createStack(Stack *s);
void push(Stack *s, char c);
char peek(Stack *s);
char pop(Stack *s);
Stack invertString(Stack *s);
int isSequenceValid(char sequence[]);

int main() {
    char sequence[1 + 1] = {'c','\0'};
    printf("Sequencia: %d", isSequenceValid(sequence));
    return 0;
}

void createStack(Stack *s) {
    s->top = -1;
}
int isFull(Stack *s) {
    if(s->top == MAX_SIZE -1) return 1;
    return 0;
}
void push(Stack *s, char c) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->content[++s->top] = c;
    printf("Item pushed in position %d\n", s->top);
}

int isEmpty(Stack *s) {
    if (s->top == -1) return 1;
    return 0;
}

char peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty");
    }
    return s->content[s->top];
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("The stack is empty");
    }
    char popped = s->content[s->top];
    s->top--;
    printf("Popped %c from the stack\n", popped);
    return popped;
} 

Stack invertString(Stack *s) {
    Stack newS;
    createStack(&newS);
    for (int i = s->top; i >= 0; i--) {
        char popped = pop(s);
        push(&newS, popped);
    }
    return newS;
}

int bemFormada(char s[], Stack stack) {
    createStack(&stack);
    for (int i = 0; s[i] != '\0'; i++) {
        char c;
        switch (s[i]) {
            case ')':   if (isEmpty(&stack)) return 0;
                        c = pop(&stack);
                        if (c != '(') return 0;
                        break;
            case ']':   if (isEmpty(&stack)) return 0;
                        c = pop(&stack);
                        if (c != '[') return 0;
                        break;
            default:    push(&stack, s[i]);
        }
    }
    return isEmpty(&stack);
}

//Escreva um programa que decida se uma string x pertence ou não ao nosso conjunto,
//c,  aca,  bcb,  abcba,  bacab,  aacaa,  bbcbb
int isSequenceValid(char sequence[]) {
    Stack s; 
    createStack(&s);
    int i = 0;
    int cPosition = -1;
    //inserir string na pilha
    while (sequence[i] != '\0') {
        if (sequence[i] == 'c') cPosition = i;
        push(&s, sequence[i]);
        i++;
    }
    //se C = 0 -> 1;
    //TODO: VERIFICAR SE O CENARIO 'CA'
    if (cPosition == 0 && s.top == 0) return 1;
    //se C = 1 -> base = topo - 2 profundidade; verificar se base != topo;
    if (cPosition == 1) {
        char base;
        char top = peek(&s);
        pop(&s);
        pop(&s);
        base = peek(&s);
        if (base == top || base == 'c') return 0; 
    }
    //se C = 2 -> base1 = topo - 4 profundidade; verificar se base != topo;
    //----base2 = topo - 3 profundidade; base2 != topo2;
    if (cPosition == 2) {
        char base1;
        char base2;
        char top1;
        char top2;
        top1 = pop(&s);
        top2 = pop(&s);
        pop(&s);
        base2 = pop(&s);
        base1 = pop(&s);
        if ((base1 == top1 || base1 == 'c') || ((base2 == top2 || base2 == 'c'))) return 0;
    }
    if(cPosition == -1) return 0;
    return 1;
}