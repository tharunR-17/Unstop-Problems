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

#include <iostream>
#include <vector>

using namespace std;


vector<int> turbine_operations(int n, int q, vector<int>& initial_flows, vector<vector<int>>& operations) {
    struct SegmentTree {
        int size;
        vector<long long> tree, lazy;

        SegmentTree(const vector<int>& a) {
            size = a.size();
            tree.resize(4 * size);
            lazy.resize(4 * size);
            build(a, 1, 0, size - 1);
        }
        void build(const vector<int>& a, int node, int l, int r) {
            if (l == r) {
                tree[node] = a[l];
                return;
            }
            int mid = (l + r) / 2;
            build(a, node * 2, l, mid);
            build(a, node * 2 + 1, mid + 1, r);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
        void push(int node, int l, int r) {
            if (lazy[node]) {
                tree[node] += (r - l + 1) * lazy[node];
                if (l != r) {
                    lazy[node * 2] += lazy[node];
                    lazy[node * 2 + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
        }
        void range_add(int L, int R, int val) { range_add(1, 0, size - 1, L, R, val); }
        void range_add(int node, int l, int r, int L, int R, int val) {
            push(node, l, r);
            if (r < L || l > R) return;
            if (L <= l && r <= R) {
                lazy[node] += val;
                push(node, l, r);
                return;
            }
            int mid = (l + r) / 2;
            range_add(node * 2, l, mid, L, R, val);
            range_add(node * 2 + 1, mid + 1, r, L, R, val);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
        long long range_sum(int L, int R) { return range_sum(1, 0, size - 1, L, R); }
        long long range_sum(int node, int l, int r, int L, int R) {
            push(node, l, r);
            if (r < L || l > R) return 0;
            if (L <= l && r <= R) return tree[node];
            int mid = (l + r) / 2;
            return range_sum(node * 2, l, mid, L, R) + range_sum(node * 2 + 1, mid + 1, r, L, R);
        }
    };

    SegmentTree seg(initial_flows);
    vector<int> answer;
    for (const auto& op : operations) {
        if (op[0] == 1) {
            seg.range_add(op[1] - 1, op[2] - 1, op[3]);
        } else {
            long long val = seg.range_sum(op[1] - 1, op[2] - 1);
            answer.push_back((int)val);
        }
    }
    return answer;
}


int main() {
    int n, q;
    cin >> n >> q;

    vector<int> initial_flows(n);
    for (int i = 0; i < n; i++) {
        cin >> initial_flows[i];
    }

    vector<vector<int>> operations(q);
    for (int i = 0; i < q; i++) {
        int op_type;
        cin >> op_type;
        operations[i].push_back(op_type);
        if (op_type == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            operations[i].push_back(l);
            operations[i].push_back(r);
            operations[i].push_back(v);
        } else if (op_type == 2) {
            int l, r;
            cin >> l >> r;
            operations[i].push_back(l);
            operations[i].push_back(r);
        }
    }

    // Call the user logic function
    vector<int> results = turbine_operations(n, q, initial_flows, operations);

    // Print results for each type 2 operation
    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}
