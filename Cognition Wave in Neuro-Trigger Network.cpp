#include <bits/stdc++.h>
using namespace std;

struct Node {
    int cnt[8]{};          // frequency of each state 0..7
    Node() { memset(cnt, 0, sizeof(cnt)); }
};

class SegTree {
    int n;
    vector<Node> tree;
    vector<uint8_t> lazy;   // pending XOR (0..7)

    // merge two nodes
    static Node combine(const Node& a, const Node& b) {
        Node res;
        for (int i = 0; i < 8; ++i)
            res.cnt[i] = a.cnt[i] + b.cnt[i];
        return res;
    }

    // apply xorMask to node u
    static void apply(Node& u, uint8_t xorMask) {
        if (xorMask == 0) return;
        int newCnt[8] = {};
        for (int i = 0; i < 8; ++i)
            newCnt[i ^ xorMask] = u.cnt[i];
        memcpy(u.cnt, newCnt, sizeof(newCnt));
    }

    void push(int idx) {
        uint8_t tag = lazy[idx];
        if (tag == 0) return;
        for (int child : {idx << 1, idx << 1 | 1}) {
            apply(tree[child], tag);
            lazy[child] ^= tag;
        }
        lazy[idx] = 0;
    }

    void build(int idx, int l, int r, const vector<int>& A) {
        if (l == r) {
            tree[idx].cnt[A[l]] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(idx << 1, l, mid, A);
        build(idx << 1 | 1, mid + 1, r, A);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }

    void update(int idx, int l, int r, int ql, int qr, uint8_t xorMask) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(tree[idx], xorMask);
            lazy[idx] ^= xorMask;
            return;
        }
        push(idx);
        int mid = (l + r) >> 1;
        update(idx << 1, l, mid, ql, qr, xorMask);
        update(idx << 1 | 1, mid + 1, r, ql, qr, xorMask);
        tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return Node();            // empty
        if (ql <= l && r <= qr) return tree[idx];
        push(idx);
        int mid = (l + r) >> 1;
        Node left = query(idx << 1, l, mid, ql, qr);
        Node right = query(idx << 1 | 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }

public:
    explicit SegTree(const vector<int>& A) {
        n = (int)A.size();
        tree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, A);
    }
    // 0-based inclusive range
    void range_xor(int l, int r, uint8_t xorMask) { update(1, 0, n - 1, l, r, xorMask); }
    Node range_query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, Q;
    if (!(cin >> N >> Q)) return 0;
    vector<int> A(N);
    for (int& x : A) cin >> x;
    SegTree st(A);

    while (Q--) {
        int type; cin >> type;
        if (type == 1) {
            int L, R, M; cin >> L >> R >> M;
            st.range_xor(L - 1, R - 1, (uint8_t)M);
        } else { // type 2
            int L, R; cin >> L >> R;
            auto node = st.range_query(L - 1, R - 1);
            int best = 0;
            for (int i = 0; i < 8; ++i) best = max(best, node.cnt[i]);
            cout << best << '\n';
        }
    }
    return 0;
}
