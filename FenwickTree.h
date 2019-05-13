//
// Created by DELL on 2018/11/14.
//

#ifndef OJONLY_FENWICKTREE_H
#define OJONLY_FENWICKTREE_H

#include <cstring>

class FenwickTree {
   public:
    FenwickTree();

    void increase(int t, int n);
    int getSum(int t);

   private:
    static const int N = 2048;
    int _arr[N];

    int lowbit(int n);
};

FenwickTree::FenwickTree() { memset(_arr, 0, sizeof(_arr)); }

void FenwickTree::increase(int t, int n) {
    for (int i = t; i <= N; i += lowbit(i)) {
        _arr[i] += n;
    }
}

int FenwickTree::lowbit(int n) { return n & (-n); }

int FenwickTree::getSum(int t) {
    int s = 0;
    for (int i = t; i; i -= lowbit(i)) {
        s += _arr[i];
    }
    return s;
}

const int N = 505;
int arr[N];
int nums[N];
int lowbit(int n) { return n & (-n); }

void add(int x, int k) {
    while (x <= N) {
        arr[x] += k;
        x += x & (-x);
    }
}

int getsum(int x) {
    int ans = 0;
    while (x) {
        ans += arr[x];
        x -= x & (-x);
    }
    return ans;
}

#endif  // OJONLY_FENWICKTREE_H
