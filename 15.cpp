/*************************************************************************
	> File Name: 15.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 05 Jul 2020 06:11:26 PM CST
 ************************************************************************/
#include <stdio.h>
#define max_n 20

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

void quick_sort(int *num, int l, int r) {
    if (l > r) return ;
    int x = l, y = r, z = num[l];
    while (x < y) {
        while (x < y && num[y] > z) --y;
        if (x < y) num[x++] = num[y];
        while (x < y && num[x] < z) ++x;
        if (x < y) num[y--] = num[x];
    }
    num[x] = z;
    quick_sort(num, l, x - 1);
    quick_sort(num, x + 1, r);
    return ;
}

int arr[max_n];

void init_arr(int *num, int n) {
    for (int i = 0; i < n; ++i) arr[i] = n - i;
    return ;
}

void output(int *num, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d\n", num[i]);
    }
    return ;
}

int main() {
    init_arr(arr, max_n);
    quick_sort(arr, 0, max_n - 1);
    output(arr, max_n);
    return 0;
}
