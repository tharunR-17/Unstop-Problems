#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

struct Node {
    int left = 0, right = 0;
    long long sum = 0;
    long long lazy = -1;
};

class PersistentSegTree {
    vector<Node> tree;
    int n;

    int clone(int node) {
        tree.push_back(tree[node]);
        return (int)tree.size() - 1;
    }

    void apply(int node, int l, int r, long long val) {
        tree[node].sum = val * (r - l + 1) % MOD;
        tree[node].lazy = val;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == -1 || l == r)
            return;

        int mid = l + (r - l) / 2;
        long long val = tree[node].lazy;

        int lc = clone(tree[node].left);
        int rc = clone(tree[node].right);

        tree[node].left = lc;
        tree[node].right = rc;

        apply(lc, l, mid, val);
        apply(rc, mid + 1, r, val);

        tree[node].lazy = -1;
    }

    int update(int node, int l, int r,
               int ql, int qr, long long val) {
        if (qr < l || r < ql)
            return node;

        int cur = clone(node);

        if (ql <= l && r <= qr) {
            apply(cur, l, r, val);
            return cur;
        }

        push(cur, l, r);

        int mid = l + (r - l) / 2;

        int lc = update(tree[cur].left, l, mid,
                        ql, qr, val);

        int rc = update(tree[cur].right, mid + 1, r,
                        ql, qr, val);

        tree[cur].left = lc;
        tree[cur].right = rc;

        tree[cur].sum =
            (tree[lc].sum + tree[rc].sum) % MOD;

        return cur;
    }

    long long query(int node, int l, int r,
                    int ql, int qr) const {
        if (qr < l || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return tree[node].sum;

        // Read lazy values without changing old versions.
        if (tree[node].lazy != -1) {
            int overlap =
                min(r, qr) - max(l, ql) + 1;

            return tree[node].lazy * overlap % MOD;
        }

        int mid = l + (r - l) / 2;

        return (query(tree[node].left, l, mid, ql, qr)
              + query(tree[node].right, mid + 1, r,
                      ql, qr)) % MOD;
    }

public:
    PersistentSegTree(int size) : n(size) {
        tree.push_back(Node());
    }

    int update(int root, int l, int r, long long val) {
        return update(root, 1, n, l, r, val);
    }

    long long query(int root, int l, int r) const {
        return query(root, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    PersistentSegTree seg(n);

    vector<int> roots(n + 1, 0);
    stack<int> st;

    for (int r = 1; r <= n; r++) {

        while (!st.empty() && a[st.top()] <= a[r])
            st.pop();

        int left = st.empty() ? 1 : st.top() + 1;

        roots[r] = seg.update(
            roots[r - 1], left, r, a[r] % MOD
        );

        st.push(r);
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int l, r;
        cin >> l >> r;

        cout << seg.query(roots[r], l, r) << '\n';
    }

    return 0;
}
