#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//O módulo deve conter as funções  criapilha,  empilha,  desempilha,  pilhavazia,  pilhacheia.
#define MAX_SIZE 100
#define MAX_LINHA 256
#define MAX_LINHAS 5

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
char *toPosFix(char *operation);
char *transpiler();

int main() {
    char sequence[] = "(a+b*c)";
    
    transpiler();
    
    
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

char *toPosFix(char *operation) {
    Stack s;
    int n = strlen(operation);
    char *result;
    result =  malloc((n + 1) * sizeof(char));
    createStack(&s);
    push(&s, operation[0]);
    int j = 0;
    for (int i = 1; operation[i] != '\0'; i++) {
        char x;
        switch (operation[i]) {
            case '+':
            case '-':
                x = pop(&s); 
                while ( x != '(') {
                    result[j++] = x;
                    x = pop(&s);
                }
                push(&s, x);
                push(&s, operation[i]);
                break;
            case '*':
            case '/':
                x = pop(&s);
                while (x != '(' && x != '+' && x != '-') {
                    result[j++] = x;
                    x = pop(&s);
                }
                push(&s, x);
                push(&s, operation[i]);

            default:
                result[j++] = operation[i];
                break;
        }
    }
    result[j++] = '\0';
    return result;
}

// 0   #4 aaa #2
// 1   bbb
// 2   CC #4 DDD #1 ee
// 3   FF #2 #4
// 4   GG hhh
// GG hhh aaa CC GG hhh DDD bbb ee
char *transpiler() {
    //ler file
    FILE *fptr = fopen("file.txt", "r");
    if (fptr == NULL) {
        printf("Not able to open the file");
        return NULL;
    }
    //entrar linha a linha
    int count = 0;
    char **lines = malloc(MAX_LINHAS * sizeof(char*));
    if (!lines) {
        perror("Erro ao alocar memória");
        fclose(fptr);
        return NULL;
    }

    char buffer[MAX_LINHA];
    while (fgets(buffer, MAX_LINHA, fptr) && count < MAX_LINHAS) {
        //armazenar cada linha
        buffer[strcspn(buffer, "\n")] = '\0';
        lines[count] = malloc(strlen(buffer) + 1);
        if (!lines[count]) {
            perror("Erro ao alocar memória para linha");
            break;
        }
        strcpy(lines[count], buffer);
        count++;        
    }

    //cria primeira pilha inversa
    Stack stack;
    createStack(&stack);
    int line_len = strlen(lines[0]);
    for (int j = line_len-1; j >= 0; j--) {
        push(&stack, lines[0][j]);
    }
    printf("%s\n", stack.content);
    int stackTop = stack.top;
    char item;
    char accResult[40];
    for (int j = 0; j <= stackTop; j++) {
        item = pop(&stack);
        //se o item da pilha não for um #, add no acc
        if (item != '#') {
            accResult[j]=item;
        } else {
            int gotoLine = peek(&stack);
            lines[gotoLine] 
        }
        // printf("%c\n", item);
    }
    printf("->%s\n", accResult);

    //iterar de traz para frente
    //add na pilha
    fclose(fptr);
    //se não encontrar retorna a linha
}