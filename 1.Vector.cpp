/*************************************************************************
	> File Name: Vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 06 Jun 2020 07:51:18 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//顺序表结构定义
typedef struct Vector {
    int *data;
    int size, length;
} Vector;

//初始化顺序表，用malloc动态开辟空间
Vector *init(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

//扩大顺序表容量
int expand(Vector *vec) {
    int extra_size = vec->size;
    int *p;
    while (extra_size) {
        p = (int *)realloc(vec->data, sizeof(int) * (vec->size + extra_size));
        if (p) break;
        extra_size /= 2;
    }
    if (extra_size == 0) return 0;
    vec->data = p;
    vec->size += extra_size;
    return 1;
}

//插入元素
int insert(Vector *vec, int index, int val) {
    if (vec == NULL) return 0;
    if (index < 0 || index > vec->length) return 0;
    if (vec->length == vec->size) {
        if (!expand(vec)) return 0;
        printf("success to expand ! the Vector size is %d\n", vec->size);
    }
    for (int i = vec->length; i > index; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[index] = val;
    vec->length += 1;
    return 1;
}

//删除元素
int erase(Vector *vec, int index) {
    if (vec == NULL) return 0;
    if (index < 0 || index >= vec->length) return 0;
    for (int i = index + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void output(Vector *vec) {
    printf("Vector : [");
    for (int i = 0; i < vec->length; i++) {
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return ;
}

//销毁顺序表
void clear(Vector *vec) {
    free(vec->data);
    free(vec);
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    Vector *vec = init(max_op);
    for (int i = 0; i < max_op * 4; i++) {
        int op = rand() % 4;
        int index = rand() % (vec->length + 3) - 1;
        int val = rand() % 100;
        switch (op) {
            case 1:
            case 2:
            case 0: {
                printf("insert %d at %d to Vector = %d\n", val, index, insert(vec, index, val));
            } break;
            case 3: {
                printf("erase a iterm at %d from Vector = %d\n", index, erase(vec, index));
            } break;
        }
        output(vec);
        printf("\n");
    }
    clear(vec);
    #undef max_op
    return 0;
}
