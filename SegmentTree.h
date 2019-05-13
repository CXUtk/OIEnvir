
template <typename T>
struct SegmentTree {
   public:
    static const int MAXN = 100005;
    T arr[MAXN];
    T ans[MAXN * 4];
    T tag[MAXN * 4];

    SegmentTree() = default;

    inline T leftson(T x) { return x << 1; }
    inline T rightson(T x) { return x << 1 | 1; }
    inline void push_up(T p) { ans[p] = ans[leftson(p)] + ans[rightson(p)]; }
    inline void push_down(T p, T l, T r) {
        T mid = (l + r) / 2;
        modify(leftson(p), l, mid, tag[p]);
        modify(rightson(p), mid + 1, r, tag[p]);
        tag[p] = 0;
    }

    void modify(T p, T l, T r, T k) {
        tag[p] = tag[p] + k;
        ans[p] = ans[p] + k * (r - l + 1);
    }

    void build(T p, T l, T r) {
        tag[p] = 0;
        if (l == r) {
            ans[p] = arr[l];
            return;
        }
        T mid = (l + r) / 2;
        build(leftson(p), l, mid);
        build(rightson(p), mid + 1, r);
        push_up(p);
    }

    T query(T x, T y, T l, T r, T p) {
        T res = 0;
        if (x <= l && y >= r) return ans[p];
        T mid = (l + r) / 2;
        push_down(p, l, r);
        if (x <= mid) res += query(x, y, l, mid, leftson(p));
        if (y > mid) res += query(x, y, mid + 1, r, rightson(p));
        return res;
    }

    void update(T x, T y, T l, T r, T p, T k) {
        if (x <= l && y >= r) {
            ans[p] += k * (r - l + 1);
            tag[p] += k;
            return;
        }
        push_down(p, l, r);
        T mid = (l + r) / 2;
        if (x <= mid) update(x, y, l, mid, leftson(p), k);
        if (y > mid) update(x, y, mid + 1, r, rightson(p), k);
        push_up(p);
    }

    inline void Update(T x, T y, T k, T maxr) { update(x, y, 1, maxr, 1, k); }
    inline T Query(T x, T y, T maxr) { return query(x, y, 1, maxr, 1); }
};