#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
typedef long long ll;
using namespace std;
const int INF = 2147483647;
const int INF2 = 0x3f3f3f3f;
const ll INF64 = 1e18;
const double INFD = 1e30;
const double EPS = 1e-6;
const double PI = 3.14159265;
const ll MOD = 1e9 + 7;
// 读入优化
inline int read() {
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
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

struct Edge {
    int to;
    int c;
};

int n, m, k;
int CASE;
const int MAXN = 100005;
vector<Edge> graph[MAXN];
int dist[MAXN];
bool vis[MAXN];

void detect(int u) {
    vis[u] = true;
    for (auto v : graph[u]) {
        if (dist[u] + v.c > dist[v.to]) {
            if (vis[v.to]) {
                printf("No");
                exit(0);
            }
            dist[v.to] = dist[u] + v.c;
            detect(v.to);
        }
    }
    vis[u] = false;
}

int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int t, a, b, c;
        scanf("%d %d %d", &t, &a, &b);
        if (t != 3) {
            scanf("%d", &c);
        }
        if (t == 1) {
            graph[b].push_back({a, c});
        } else if (t == 2) {
            graph[a].push_back({b, -c});
        } else {
            graph[a].push_back({b, 0});
            graph[b].push_back({a, 0});
        }
    }
    for (int i = 1; i <= n; i++) {
        graph[0].push_back({i, 0});
        dist[i] = -INF;
    }

    detect(0);
    printf("Yes");

    return 0;
}