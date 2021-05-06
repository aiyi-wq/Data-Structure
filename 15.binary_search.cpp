/*************************************************************************
	> File Name: 15.binary_search.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 05 Jul 2020 07:21:41 PM CST
 ************************************************************************/
#include <stdio.h>

#define P(func, args...) {
    printf("")
}

//1 3 5 7 9 10
int binary_search1(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == x) return mid;
        if (num[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

//11111111000000, 虚拟头指针
int binary_search2(int *num, int n) {
    int head = -1, tail = n - 1;
    while (head < tail) {
        int mid = (head + 1 + tail) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;
}

//0000000011111111, 虚拟尾指针
int binary_search3(int *num, int n) {
    int head = 0, tail = n;
    while (head < tail) {
        int mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return head == n ? -1 : head;
}
int main() {
    int arr1[10] = {1, 3, 5, 7, 9, 11, 13, 17, 19, 21};
    int arr1[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    int arr1[10] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
    P(binary_search1, arr1, 10, 7);
    P(binary_search2, arr2, 10);
    P(binary_search3, arr3, 10);
    return 0;
}
