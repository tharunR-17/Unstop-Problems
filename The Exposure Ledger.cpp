#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Fenwick Tree (Binary Indexed Tree) for dynamic flagging and auditing
struct FenwickTree {
    int n;
    vector<int> tree;
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    void add(int i, int delta) {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }

    int query(int i) const {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    int queryRange(int l, int r) const {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

// Persistent Segment Tree for static range k-th smallest element
struct Node {
    int count;
    int left_child;
    int right_child;
};

const int MAX_NODES = 200000 * 25; // Enough nodes for N = 200,000 and depth ~18
Node tree_nodes[MAX_NODES];
int node_cnt = 0;

int build(int l, int r) {
    int id = ++node_cnt;
    tree_nodes[id] = {0, 0, 0};
    if (l == r) return id;
    int mid = l + (r - l) / 2;
    tree_nodes[id].left_child = build(l, mid);
    tree_nodes[id].right_child = build(mid + 1, r);
    return id;
}

int update(int prev_id, int l, int r, int val_idx) {
    int id = ++node_cnt;
    tree_nodes[id] = tree_nodes[prev_id];
    tree_nodes[id].count++;
    if (l == r) return id;

    int mid = l + (r - l) / 2;
    if (val_idx <= mid) {
        tree_nodes[id].left_child = update(tree_nodes[prev_id].left_child, l, mid, val_idx);
    } else {
        tree_nodes[id].right_child = update(tree_nodes[prev_id].right_child, mid + 1, r, val_idx);
    }
    return id;
}

int queryKth(int left_root, int right_root, int l, int r, int k) {
    if (l == r) return l;

    int count_left = tree_nodes[tree_nodes[right_root].left_child].count - 
                     tree_nodes[tree_nodes[left_root].left_child].count;
    int mid = l + (r - l) / 2;

    if (count_left >= k) {
        return queryKth(tree_nodes[left_root].left_child, tree_nodes[right_root].left_child, l, mid, k);
    } else {
        return queryKth(tree_nodes[left_root].right_child, tree_nodes[right_root].right_child, mid + 1, r, k - count_left);
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    vector<int> unique_vals;
    unique_vals.reserve(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        unique_vals.push_back(a[i]);
    }

    // Coordinate compression for exposure values
    sort(unique_vals.begin(), unique_vals.end());
    unique_vals.erase(unique(unique_vals.begin(), unique_vals.end()), unique_vals.end());
    int m = unique_vals.size();

    auto get_compressed_idx = [&](int val) {
        return lower_bound(unique_vals.begin(), unique_vals.end(), val) - unique_vals.begin() + 1;
    };

    // Build persistent segment tree versions
    vector<int> roots(n + 1, 0);
    roots[0] = build(1, m);

    for (int i = 1; i <= n; i++) {
        int c_idx = get_compressed_idx(a[i]);
        roots[i] = update(roots[i - 1], 1, m, c_idx);
    }

    // Fenwick tree and state array for FLAG / AUDIT operations
    FenwickTree bit(n);
    vector<int> flagged(n + 1, 0);

    for (int i = 0; i < q; i++) {
        string type;
        cin >> type;

        if (type == "RANK") {
            int l, r, k;
            cin >> l >> r >> k;
            int ans_compressed = queryKth(roots[l - 1], roots[r], 1, m, k);
            cout << unique_vals[ans_compressed - 1] << "\n";
        } else if (type == "FLAG") {
            int idx;
            cin >> idx;
            if (flagged[idx] == 0) {
                flagged[idx] = 1;
                bit.add(idx, 1);
            } else {
                flagged[idx] = 0;
                bit.add(idx, -1);
            }
        } else if (type == "AUDIT") {
            int l, r;
            cin >> l >> r;
            cout << bit.queryRange(l, r) << "\n";
        }
    }

    return 0;
}
