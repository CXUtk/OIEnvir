#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;

const int INF = 2147483647;
const int INF2 = 0x3f3f3f3f;
const ll INF64 = 1e18;
const double INFD = 1e30;
const double EPS = 1e-8;
const double PI = 3.1415926;
const ll MOD = 1e9 + 7;
struct Edge {
    int fr;
    int to;
    int cap;
    int flow;
    Edge() = default;
    Edge(int fr, int to, int cap, int flow)
        : fr(fr), to(to), cap(cap), flow(flow) {}
};
const int MAXN = 1005;
struct EKarp {
    int n, m;
    vector<Edge> edges;
    vector<int> G[MAXN];
    int a[MAXN];
    int p[MAXN];

    void init() {
        for (int i = 1; i <= n; i++) {
            G[i].clear();
        }
        edges.clear();
    }
    void addEdge(int f, int t, int c) {
        edges.push_back({f, t, c, 0});
        edges.push_back({t, f, 0, 0});
        m = edges.size();
        G[f].push_back(m - 2);
        G[t].push_back(m - 1);
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        for (;;) {
            memset(a, 0, sizeof(a));
            queue<int> Q;
            Q.push(s);
            a[s] = INF2;
            while (!Q.empty()) {
                int x = Q.front();
                Q.pop();
                for (auto g : G[x]) {
                    Edge& e = edges[g];
                    if (!a[e.to] && e.cap > e.flow) {
                        p[e.to] = g;
                        a[e.to] = min(a[x], e.cap - e.flow);
                        Q.push(e.to);
                    }
                }
                if (a[t]) break;
            }
            if (!a[t]) break;
            for (int u = t; u != s; u = edges[p[u]].fr) {
                edges[p[u]].flow += a[t];
                edges[p[u] ^ 1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
    EKarp();
    ~EKarp();
};
