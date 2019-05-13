//
// Created by DELL on 2018/10/6.
//

#ifndef OJONLY_UTILS_H
#define OJONLY_UTILS_H
#include <cstring>
#include <queue>
#include <random>
#include <vector>
using namespace std;
typedef long long ll;

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point& b) const { return this->x < b.x; }
};

struct Edge {
    int fr;
    int to;
    int cap;
    int flow;
    Edge() = default;
    Edge(int fr, int to, int cap, int flow)
        : fr(fr), to(to), cap(cap), flow(flow) {}
};

struct Edge {
    int fr;
    int to;
    int dis;
    Edge() = default;
    Edge(int fr, int to, int dis) : fr(fr), to(to), dis(dis) {}
    bool operator<(const Edge& b) const { return this->dis < b.dis; }
};

struct Edge {
    int to;
    int dis;
    Edge() = default;
    Edge(int to, int dis) : to(to), dis(dis) {}
    bool operator<(const Edge& b) const { return this->dis < b.dis; }
};

ll gcd(ll x, ll y) { return !y ? x : gcd(y, x % y); }

int phi[100000];

void phis(int MAXN) {
    phi[1] = 1;
    for (int i = 2; i <= MAXN; i++) {
        if (!phi[i]) {
            for (int j = i; j <= MAXN; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

std::vector<int> primes;
void phiwithP(int x) {
    phi[1] = 1;
    for (int i = 2; i <= x; i++) {
        if (!phi[i]) {
            primes.push_back(i);
            for (int j = i; j <= x; j += i) {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

std::set<int> primes;
bool vis[MAXN];
void getprime(int x) {
    for (int i = 2; i <= x; i++) {
        if (!vis[i]) {
            primes.insert(i);
            for (int j = i * 2; j <= x; j += i) {
                vis[j] = true;
            }
        }
    }
}

int mob[100000];
void mobius(int x) {
    mob[1] = 1;
    for (int i = 1; i <= x; i++) {
        for (int j = i * 2; j <= x; j += i) {
            mob[j] = -mob[i];
        }
    }
}

bool vis[100000];
void mobiusWithP(int x) {
    mob[1] = 1;
    for (int i = 2; i <= x; i++) {
        if (!vis[i]) {
            primes.push_back(i);
            mob[i] = -1;
        }
        for (auto p : primes) {
            if (i * p > x) break;
            vis[i * p] = true;
            if (i % p)
                mob[i * p] = -mob[i];
            else {
                mob[i * p] = 0;
                break;
            }
        }
    }
}

ll euler(ll n) {
    ll res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n < i) break;
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}

int find(int p) {
    while (p != parent[p]) {
        parent[p] = parent[parent[p]];  // path compression by halving
        p = parent[p];
    }
    return p;
}

bool visited[1];
vector<int> graph[1];
vector<int> orders;

vector<Edge> _edges[1];

void dijkstra() {
    int dist[1];
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        Q;
    Q.push({0, 1});
    dist[1] = 0;
    bool vis[1];
    while (!Q.empty()) {
        auto p = Q.top();
        Q.pop();
        if (vis[p.second]) continue;
        vis[p.second] = true;
        if (p.first != dist[p.second]) continue;
        for (auto v : _edges[p.second]) {
            if (dist[p.second] + v.dis < dist[v.to]) {
                dist[v.to] = dist[p.second] + v.dis;
                Q.push({dist[v.to], v.to});
            }
        }
    }
}

void topoSort(int u) {
    visited[u] = true;

    for (auto v : graph[u])
        if (!visited[v]) topoSort(v);

    orders.push_back(u);
}

// 读入优化
template <typename T>
inline T read() {
    T X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

int quickM(ll x, ll p, int mod) {
    if (mod == 0) return 1;
    x %= mod;
    ll ans = 1;
    while (p) {
        if (p & 1) ans = ans * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return ans;
}

void extgcd(ll a, ll b, ll& d, ll& x, ll& y) {
    if (!b) {
        d = a;
        x = 1;
        y = 0;
    } else {
        extgcd(b, a % b, d, y, x);
        y -= x * (a / b);
    }
}

inline ll getInv(ll x, ll mod) {
    ll g, a, b;
    extgcd(x, mod, g, a, b);
    return (a % mod + mod) % mod;
}

struct River {
    int p, l, v;
};

void combination(int n, int r) {
    int comb = (1 << r) - 1;
    while (comb < 1 << n) {
        // 处理组合状态
        int x = comb & -comb, y = comb + x;
        comb = ((comb & ~y) / x >> 1) | y;
    }
}

int arr[1];

void mono_queue(int n, int k) {
    deque<int> Q;
    for (int i = 0; i < n; i++) {
        while (!Q.empty() && Q.back() > arr[i]) {
            Q.pop_back();
        }
        Q.push_back(arr[i]);
        if (i >= k && Q.front() == arr[i - k]) {
            Q.pop_front();
        }
        if (i >= k - 1) printf("%d ", Q.front());
    }
}

bool next_permutation1(int* beg, int* end) {
    int* p = end - 1;
    while (p > beg && *(p - 1) > *p) p--;
    if (p == beg) return false;
    int* div = p - 1;
    while (p != end - 1 && *(p + 1) > *div) p++;
    swap(*div, *p);
    sort(div + 1, end);
    return true;
}

mt19937 gen(rand());
bool Miller_Rabin(ll n) {
    if (n == 2) return true;
    if (n < 2 || !(n & 1)) return false;
    for (int i = 1; i < 10; i++) {
        ll a = gen() % (n - 1) + 1;
        if (quickM(a, n - 1, n) != 1) return false;
    }
    return true;
}

int minn[1][1];
void RMQ(int x) {
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i <= x; i++) {
            if (i + (1 << j) - 1 > x) continue;
            minn[i][j] =
                std::min(minn[i][j - 1], minn[i + (1 << (j - 1))][j - 1]);
        }
    }
}

#endif  // OJONLY_UTILS_H
