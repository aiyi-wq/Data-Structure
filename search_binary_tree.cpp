/*************************************************************************
	> File Name: search_binary_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 21 Jul 2020 07:02:00 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild, *father;
} Node;

Node *init(int data, Node *father) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->lchild = node->rchild = NULL;
    node->data = data;
    node->father = father;
    return node;
}
//插入
Node *insert(Node *node, int val) {
    if (!node) {
        node = init(val, NULL);
    } else if (val > node->data) {
        if (!node->rchild) {
            node->rchild = init(val, node);
        } else {
            node->rchild = insert(node->rchild, val);
        }
    } else if (val < node->data) {
        if (!node->lchild) {
            node->lchild = init(val, node);
        } else {
            node->lchild = insert(node->lchild, val);
        }
    }
    return node;
}
//查找要删除的值所在节点
Node *search(Node *node, int val) {
    if (!node || node->data == val) {
        return node;
    } else if (val > node->data) {
        if (!node->rchild) {
            return NULL;
        } else {
            return search(node->rchild, val);
        }
    } else {
        if (!node->lchild) {
            return NULL;
        } else {
            return search(node->lchild, val);
        }
    }
}
//找前驱
Node *predecessor(Node *node) {
    Node *temp = node->lchild;
    while (temp && temp->rchild) {
        temp = temp->rchild;
    }
    return temp;
}
//找后继
Node *successor(Node *node) {
    Node *temp = node->rchild;
    while (temp && temp->lchild) {
        temp = temp->lchild;
    }
    return temp;
}
//删除节点
void remove_node(Node *node) {
    Node *temp = NULL;
    if (node->lchild) {
        temp = node->lchild;
        temp->father = node->father;
    }
    if (node->rchild) {
        temp = node->rchild;
        temp->father = node->father;
    }
    if (node->father->lchild == node) {
        node->father->lchild = temp;
    } else {
        node->father->rchild = temp;
    }
    node->lchild = node->rchild = NULL;
    free(node);
    return ;
}
//递归删除节点的值
int delete_tree(Node *node, int val) {
    Node *temp = search(node, val);
    if (!temp) return 0;
    Node *in = predecessor(temp);
    if (!in) in = successor(temp);
    if (in) {
        temp->data = in->data;
        remove_node(in);
    } else {
        remove_node(temp);
    }
    return 1;
}

//中序遍历
int inorder(Node *node) {
    if (!node) return 0;
    node->lchild && inorder(node->lchild);
    printf("%d ", node->data);
    node->rchild && inorder(node->rchild);
    return 1;
}
//清空二叉树
void clear(Node *node) {
    if (node) {
        if (node->lchild) {
            clear(node->lchild);
        }
        if (node->rchild) {
            clear(node->rchild);
        }
        free(node);
    }
    return ;
}

int main() {
    Node *binarytree = NULL;
    int arr[10] = {3, 6, 7, 9, 2, 1, 8, 4, 10, 5};
    for (int i = 0; i < 10; ++i) {
        binarytree = insert(binarytree, arr[i]);
    }
    int val;
    scanf("%d", &val);
    delete_tree(binarytree, val);
    inorder(binarytree);
    printf("\n");
    clear(binarytree);
    return 0;
}
