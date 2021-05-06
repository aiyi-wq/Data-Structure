/*************************************************************************
	> File Name: 4.Stack.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Jun 2020 03:33:29 PM CST
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

typedef struct Stack {
    int *data;
    int size, top;
} Stack;

Stack *init(int);
void clear(Stack *);
int top(Stack *);
int empty(Stack *);
int push(Stack *, int);
int pop(Stack *);
int expand(Stack *);
void output(Stack *);

int main() {
    srand(time(0));
    #define max_op 20
    Stack *s = init(2);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the Stack = %d\n", val, push(s, val));
            } break;
            case 3: {
                printf("pop %d from the Stack = %d\n", top(s), pop(s));
            } break;
        }
        output(s), printf("\n");
    }
    #undef max_op
    clear(s);
    return 0;
}

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) *n);
    s->size = n;
    s->top = -1;
    return s;
}

int top(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return (s->top == -1);
}

int expand(Stack *s) {
    int extra_size = s->size;
    int *p;
    while (extra_size) {
        p = (int *)malloc(sizeof(int) * (s->size + extra_size));
        if (p) break;
        extra_size >>= 1;
    }
    if (p == NULL) return 0;
    for (int i = 0; i <= s->top; i++) {
        p[i] = s->data[i];
    }
    free(s->data);
    s->data = p;
    s->size += extra_size;
    return 1;
}


int push(Stack *s, int val) {
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) {
        if (!expand(s)) return 0;
        printf("\033[1;32m success to expand! the stack's size is %d\n \033[0m", s->size);
    }
    s->data[++s->top] = val;
    return 1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void output(Stack *s) {
    printf("Stack(%d) = [", s->top + 1);
    for (int i = 0; i <= s->top; i++) {
        (i) && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("]\n");
    return ;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}
