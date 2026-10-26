#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

struct SegmentTree {
    int n;
    vector<ll> sumG, sumH;
    vector<ll> lazyA, lazyB, lazyC;

    SegmentTree(int n) : n(n) {
        int sz = 4 * n + 5;
        sumG.assign(sz, 0);
        sumH.assign(sz, 0);
        lazyA.assign(sz, 0);
        lazyB.assign(sz, 0);
        lazyC.assign(sz, 0);
    }

    void apply(int node, int l, int r,
               ll A, ll B, ll C) {
        ll oldG = sumG[node];

        sumH[node] += B * oldG + (r - l + 1LL) * C;
        sumG[node] += (r - l + 1LL) * A;

        lazyC[node] += B * lazyA[node] + C;
        lazyA[node] += A;
        lazyB[node] += B;
    }

    void push(int node, int l, int r) {
        if (l == r)
            return;

        if (lazyA[node] == 0 &&
            lazyB[node] == 0 &&
            lazyC[node] == 0)
            return;

        int mid = (l + r) / 2;

        apply(node * 2, l, mid,
              lazyA[node], lazyB[node], lazyC[node]);

        apply(node * 2 + 1, mid + 1, r,
              lazyA[node], lazyB[node], lazyC[node]);

        lazyA[node] = 0;
        lazyB[node] = 0;
        lazyC[node] = 0;
    }

    void pull(int node) {
        sumG[node] = sumG[node * 2] + sumG[node * 2 + 1];
        sumH[node] = sumH[node * 2] + sumH[node * 2 + 1];
    }

    void update(int node, int l, int r,
                int ql, int qr, ll A, ll B, ll C) {
        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, A, B, C);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, A, B, C);
        update(node * 2 + 1, mid + 1, r, ql, qr, A, B, C);

        pull(node);
    }

    void addG(int l, int r, ll value) {
        if (l <= r)
            update(1, 0, n - 1, l, r, value, 0, 0);
    }

    void accumulate(int l, int r) {
        if (l <= r)
            update(1, 0, n - 1, l, r, 0, 1, 0);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;

        if (ql <= l && r <= qr)
            return sumH[node];

        push(node, l, r);

        int mid = (l + r) / 2;

        return query(node * 2, l, mid, ql, qr)
             + query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    ll query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

struct Query {
    int l, r, idx;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> a(N);

    for (int i = 0; i < N; i++)
        cin >> a[i];

    int Q;
    cin >> Q;

    vector<Query> queries(Q);

    for (int i = 0; i < Q; i++) {
        cin >> queries[i].l >> queries[i].r;
        --queries[i].l;
        --queries[i].r;
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end(),
         [](const Query& x, const Query& y) {
             return x.r < y.r;
         });

    SegmentTree seg(N);

    vector<int> maxStack, minStack;
    vector<ll> ans(Q);

    int qi = 0;

    for (int r = 0; r < N; r++) {
        while (!maxStack.empty() &&
               a[maxStack.back()] <= a[r]) {
            int p = maxStack.back();
            maxStack.pop_back();

            int left = maxStack.empty()
                     ? 0 : maxStack.back() + 1;

            seg.addG(left, p, (ll)a[r] - a[p]);
        }

        maxStack.push_back(r);

        while (!minStack.empty() &&
               a[minStack.back()] >= a[r]) {
            int p = minStack.back();
            minStack.pop_back();

            int left = minStack.empty()
                     ? 0 : minStack.back() + 1;

            seg.addG(left, p, (ll)a[p] - a[r]);
        }

        minStack.push_back(r);

        seg.accumulate(0, r);

        while (qi < Q && queries[qi].r == r) {
            ans[queries[qi].idx] =
                seg.query(queries[qi].l, r);
            qi++;
        }
    }

    ll best = -1;
    int bestIndex = 1;

    for (int i = 0; i < Q; i++) {
        if (i > 0)
            cout << ' ';

        cout << ans[i];

        if (ans[i] > best) {
            best = ans[i];
            bestIndex = i + 1;
        }
    }

    cout << '\n' << bestIndex << '\n';

    return 0;
}
