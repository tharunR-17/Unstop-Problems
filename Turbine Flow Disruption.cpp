#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 2e5 + 5;
int seg[4 * MAXN], lazy[4 * MAXN];

void build(vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) seg[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        seg[v] = seg[v * 2] + seg[v * 2 + 1];
    }
}

void push(int v, int tl, int tr) {
    if (lazy[v]) {
        seg[v] += lazy[v] * (tr - tl + 1);
        if (tl != tr) {
            lazy[v * 2] += lazy[v];
            lazy[v * 2 + 1] += lazy[v];
        }
        lazy[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int addend) {
    push(v, tl, tr);
    if (l > r) return;
    if (l == tl && r == tr) {
        lazy[v] += addend;
        push(v, tl, tr);
    } else {
        int tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), addend);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
        seg[v] = seg[v * 2] + seg[v * 2 + 1];
    }
}

int query(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (l > r) return 0;
    if (l <= tl && tr <= r) return seg[v];
    int tm = (tl + tr) / 2;
    return query(v * 2, tl, tm, l, min(r, tm)) +
           query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    build(a, 1, 0, n - 1);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r, v; cin >> l >> r >> v;
            update(1, 0, n - 1, l - 1, r - 1, v);
        } else {
            int l, r; cin >> l >> r;
            cout << query(1, 0, n - 1, l - 1, r - 1) << "\n";
        }
    }
}
