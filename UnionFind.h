//
// Created by DELL on 2018/11/14.
//

#ifndef OJONLY_UNIONFIND_H
#define OJONLY_UNIONFIND_H

#include <cstring>

class UnionFind {
   public:
    UnionFind() {}
    inline int find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];  // path compression by halving
            x = parent[x];
        }
        return x;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    void join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (rank[x] < rank[y])
            parent[x] = y;
        else {
            parent[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
        }
    }
    void clear(int n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    static const int N = 100005;
    int parent[N];
    int rank[N];
};

#endif  // OJONLY_UNIONFIND_H
