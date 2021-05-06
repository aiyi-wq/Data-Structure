/*************************************************************************
	> File Name: 3.Queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 20 Jun 2020 02:49:20 PM CST
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Queue {
    int *data;
    int size, head, tail, cnt;
} Queue;

//初始化队列
Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->head = q->tail = q->cnt = 0;
    return q;
}

//首地址元素
int front(Queue *q) {
    return q->data[q->head];
}
//判断队列是否为空
int empty(Queue *q) {
    return q->cnt == 0;
}

//扩容
int expand(Queue *q) {
    int extra_size = q->size;
    int *p;
    while (extra_size) {
        p = (int *)malloc(sizeof(int) * (q->size + extra_size));
        if (p) break;
        extra_size >>= 1;
    }
    if (p == NULL) return 0;
    for (int i = q->head, j = 0; j < q->cnt; j++) {
        p[j] = q->data[(i + j) % q->size];
    }
    free(q->data);
    q->data = p;
    q->size += extra_size;
    q->head = 0;
    q->tail = q->cnt;
    return 1;
}

//插入元素，入队
int push(Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) {
        if (!expand(q)) return 0;
        printf("\033[1;32m success to expand! the vector""\033 size is %d\n \033[0m", q->size);
    }
    q->data[q->tail++] = val;
    if (q->tail == q->size) q->tail -= q->size;
    q->cnt += 1;
    return 1;
}

//删除元素，出队

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head++;
    if (q->head == q->size) q->head -= q->size;
    q->cnt -= 1;
    return 1;
}

void output(Queue *q) {
    printf("Queue : [");
    for (int i = q->head, j = 0; j < q->cnt; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j)] % q->size);
    }
    printf("]\n");
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    Queue *q = init(1);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the Queue = %d\n", val, push(q, val));
            } break;
            case 3: {
                printf("pop %d from the Queue = %d\n", front(q), pop(q));
            } break;
        }
        output(q), printf("\n");
    }
    clear(q);
    return 0;
}
