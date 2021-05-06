/*************************************************************************
	> File Name: table_to_queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 27 Jun 2020 04:34:59 PM CST
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int n;
} Tree;

typedef struct Stack {
    Node **data;
    int top, size;
} Stack;

typedef struct Queue {
    Node **data;
    int size, head, tail, cnt;
} Queue;

Node *init_node(char val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Tree *init_tree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

Stack *init_stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->size = n;
    s->top = -1;
    return s;
}

Node *top(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

int push(Stack *s, Node *val) {
    if (s == NULL) return 0;
    if (s->top == s->size - 1) return 0;
    s->data[++s->top] = val;
    return 1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    s->top -= 1;
    return 1;
}

Queue *init_queue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (Node **)malloc(sizeof(Node *) * n);
    q->size = n;
    q->head = q->tail = q->cnt = 0;
    return q;
}

Node *front(Queue *q) {
    return q->data[q->head];
}

int queue_empty(Queue *q) {
    return q->cnt == 0;
}

int queue_push(Queue *q, Node *val) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) return 0;
    q->data[q->tail++] = val;
    if (q->tail == q->size) q->tail -= q->size;
    q->cnt++;
    return 1;
}

int queue_pop(Queue *q) {
    if (q == NULL) return 0;
    if (queue_empty(q)) return 0;
    q->head++;
    if (q->head == q->size) q->head -= q->size;
    q->cnt--;
    return 1;
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
} 

void clear_node(Node *root) {
    if (root == NULL) return ;
    clear_node(root->lchild);
    clear_node(root->rchild);
    free(root);
    return ;
}

void clear_tree(Tree *tree) {
    if (tree == NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}

void clear_stack(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

Node *build(const char *str, int *node_num) {
    Stack *s = init_stack(strlen(str));
    Node *temp = NULL, *p = NULL;
    int flag = 0;
    while (str[0]) {
        switch (str[0]) {
            case '(':
                push(s, temp);
                flag = 0;
                break;
            case ')':
                p = top(s);
                pop(s);
                break;
            case ',':
                flag = 1;
                break;
            case ' ':
                break;
            default:
                temp = init_node(str[0]);
                if (!empty(s) && flag == 0) {
                    top(s)->lchild = temp;
                } else if (!empty(s) && flag == 1) {
                    top(s)->rchild = temp;
                }
                ++(*node_num);
                break;
        }
        ++str;
    }
    clear_stack(s);
    if (temp && !p) p = temp;
    return p;
}

void output(Tree *tree) {
    if (tree == NULL) return ;
    if (tree->root == NULL) return ;
    Queue *q = init_queue(tree->n);
    queue_push(q, tree->root);
    int flag = 0;
    while (!queue_empty(q)) {
        Node *l = front(q)->lchild;
        Node *r = front(q)->rchild;
        l && queue_push(q, l);
        r && queue_push(q, r);
        flag++ && printf(" ");
        printf("%c", front(q)->data);
        queue_pop(q);
    }
    printf("\n");
    clear_queue(q);
    return ;
}

int main() {
    char str[100000] = {0};
    int node_num = 0;
    scanf("%[^\n]s", str);
    Tree *tree = init_tree();
    tree->root = build(str, &node_num);
    tree->n = node_num;
    output(tree);
    clear_tree(tree);
    return 0;
}
