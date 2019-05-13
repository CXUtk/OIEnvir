#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
template <typename T>
struct MinPQ {
   public:
    static const int MAX_NUM = 500005;
    T heap[MAX_NUM];
    int n;

    inline void push(T item) {
        heap[++n] = item;
        swim(n);
    }
    inline T top() const { return heap[1]; }
    inline void pop() {
        if (empty()) return;
        swap(heap[1], heap[n--]);
        sink(1);
    }
    inline bool empty() const { return n == 0; }
    MinPQ() { n = 0; }
    ~MinPQ() {}

    inline void swim(int k) {
        while (k > 1 && heap[k / 2] > heap[k]) {
            swap(heap[k / 2], heap[k]);
            k >>= 1;
        }
    }

    inline void sink(int k) {
        while ((k << 1) <= n) {
            int j = k << 1;
            if (j < n && heap[j] > heap[j + 1]) j++;
            if (!(heap[k] > heap[j])) break;
            swap(heap[k], heap[j]);
            k = j;
        }
    }
};
