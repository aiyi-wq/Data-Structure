/*************************************************************************
	> File Name: 循环左移.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 29 Sep 2020 08:48:39 AM CST
 ************************************************************************/
//题目将n(n>1)个整数存放在一维数组R中，设计一个算法，将R中的序列循环左移P(0<P<n)个位置
//采用的是将R中前P个元素逆置，再将剩下的元素逆置，最后将R中所有的元素再整体做一次逆置操作

#include<iostream>
using namespace std;
#define N 50

void Reverse(int R[], int l, int r) {
    for (int i = l, j = r; i < j; ++i, --j) {
        int temp = R[i];
        R[i] = R[j];
        R[j] = temp;
    }
}

void RCR(int R[], int n, int p) {
    if (p <= 0 || p >= n) 
        cout << "ERROR" << endl;
    else {
        Reverse(R, 0, p - 1);
        Reverse(R, p, n - 1);
        Reverse(R, 0, n - 1);
    }
}

int main() {
    int R[N], n, L;
    cin >> L >> n;
    for (int i = 0; i <= n - 1; ++i)
        cin >> R[i];
    RCR(R, n, L);
    cout << R[0];
    for (int i = 1; i <= n - 1; ++i)
        cout << " " << R[i];
    cout << endl;
    return 0;
}
