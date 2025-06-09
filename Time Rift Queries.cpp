#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *left, *right;
    int count;

    Node(Node* l = nullptr, Node* r = nullptr, int c = 0) : left(l), right(r), count(c) {}
};

class PersistentSegmentTree {
public:
    vector<int> values;
    unordered_map<int, int> val_to_idx;
    int n;

    PersistentSegmentTree(const vector<int>& vals) {
        values = vals;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        n = values.size();
        for (int i = 0; i < n; ++i)
            val_to_idx[values[i]] = i;
    }

    Node* build(int l, int r) {
        if (l == r) return new Node();
        int m = (l + r) / 2;
        return new Node(build(l, m), build(m + 1, r));
    }

    Node* update(Node* prev, int l, int r, int idx, int delta) {
        if (l == r) return new Node(nullptr, nullptr, prev->count + delta);
        int m = (l + r) / 2;
        if (idx <= m) {
            Node* left = update(prev->left, l, m, idx, delta);
            return new Node(left, prev->right, left->count + prev->right->count);
        } else {
            Node* right = update(prev->right, m + 1, r, idx, delta);
            return new Node(prev->left, right, prev->left->count + right->count);
        }
    }

    int query(Node* u, Node* v, int l, int r, int k) {
        if (l == r) return values[l];
        int m = (l + r) / 2;
        int cnt = v->left->count - u->left->count;
        if (cnt >= k) return query(u->left, v->left, l, m, k);
        else return query(u->right, v->right, m + 1, r, k - cnt);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> A(N);
    vector<tuple<int, int, int>> updates;
    vector<int> all_values;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        all_values.push_back(A[i]);
    }

    for (int i = 0; i < M; ++i) {
        int pos, val, base;
        cin >> pos >> val >> base;
        updates.push_back(make_tuple(pos, val, base));
        all_values.push_back(val);
    }

    int Q;
    cin >> Q;
    vector<tuple<int, int, int, int>> queries(Q);
    for (int i = 0; i < Q; ++i) {
        int v, l, r, k;
        cin >> v >> l >> r >> k;
        queries[i] = make_tuple(v, l, r, k);
    }

    PersistentSegmentTree pst(all_values);

    vector<vector<int>> versions = {A};
    for (size_t i = 0; i < updates.size(); ++i) {
        int pos = get<0>(updates[i]);
        int val = get<1>(updates[i]);
        int base = get<2>(updates[i]);
        vector<int> new_version = versions[base];
        new_version[pos - 1] = val;
        versions.push_back(new_version);
    }

    vector<vector<Node*>> roots;
    for (size_t i = 0; i < versions.size(); ++i) {
        vector<Node*> root_list;
        root_list.push_back(pst.build(0, pst.n - 1));
        for (size_t j = 0; j < versions[i].size(); ++j) {
            int idx = pst.val_to_idx[versions[i][j]];
            root_list.push_back(pst.update(root_list.back(), 0, pst.n - 1, idx, 1));
        }
        roots.push_back(root_list);
    }

    for (size_t i = 0; i < queries.size(); ++i) {
        int v = get<0>(queries[i]);
        int l = get<1>(queries[i]);
        int r = get<2>(queries[i]);
        int k = get<3>(queries[i]);
        Node* rootL = roots[v][l - 1];
        Node* rootR = roots[v][r];
        int ans = pst.query(rootL, rootR, 0, pst.n - 1, k);
        cout << ans << '\n';
    }

    return 0;
}
