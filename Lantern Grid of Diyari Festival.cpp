#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll sum;
    int mx, se, cnt;
};

const int MAXN = 200000 + 5;

int n, q;
int a[MAXN];
Node st[MAXN * 4];

Node mergeNode(const Node &L, const Node &R) {
    Node res;
    res.sum = L.sum + R.sum;

    if (L.mx > R.mx) {
        res.mx = L.mx;
        res.cnt = L.cnt;
        res.se = max(L.se, R.mx);
    } else if (L.mx < R.mx) {
        res.mx = R.mx;
        res.cnt = R.cnt;
        res.se = max(R.se, L.mx);
    } else {
        res.mx = L.mx;
        res.cnt = L.cnt + R.cnt;
        res.se = max(L.se, R.se);
    }

    return res;
}

void build(int p, int l, int r) {
    if (l == r) {
        st[p].sum = a[l];
        st[p].mx = a[l];
        st[p].se = -1;
        st[p].cnt = 1;
        return;
    }

    int m = (l + r) >> 1;
    build(p << 1, l, m);
    build(p << 1 | 1, m + 1, r);
    st[p] = mergeNode(st[p << 1], st[p << 1 | 1]);
}

void apply(int p, int x) {
    if (st[p].mx <= x) return;
    st[p].sum -= 1LL * (st[p].mx - x) * st[p].cnt;
    st[p].mx = x;
}

void push(int p) {
    apply(p << 1, st[p].mx);
    apply(p << 1 | 1, st[p].mx);
}

void range_chmin(int p, int l, int r, int ql, int qr, int x) {
    if (r < ql || l > qr || st[p].mx <= x)
        return;

    if (ql <= l && r <= qr && st[p].se < x) {
        apply(p, x);
        return;
    }

    push(p);

    int m = (l + r) >> 1;
    range_chmin(p << 1, l, m, ql, qr, x);
    range_chmin(p << 1 | 1, m + 1, r, ql, qr, x);

    st[p] = mergeNode(st[p << 1], st[p << 1 | 1]);
}

ll range_sum(int p, int l, int r, int ql, int qr) {
    if (r < ql || l > qr)
        return 0;

    if (ql <= l && r <= qr)
        return st[p].sum;

    push(p);

    int m = (l + r) >> 1;
    return range_sum(p << 1, l, m, ql, qr) +
           range_sum(p << 1 | 1, m + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            range_chmin(1, 1, n, l, r, v);
        } else {
            int l, r;
            cin >> l >> r;
            cout << range_sum(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}
