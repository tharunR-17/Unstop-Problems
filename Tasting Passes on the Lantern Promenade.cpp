#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXV = 1000000;

struct Node {
    long long total_portions;
    long long total_cost;
    int left, right;
};

vector<Node> tree;
vector<int> roots;

// Insert / update persistent segment tree dynamically
int update(int prev_node, int L, int R, int pos, long long add_portions, long long add_cost) {
    int curr = tree.size();
    tree.push_back(prev_node ? tree[prev_node] : Node{0, 0, 0, 0});
    tree[curr].total_portions += add_portions;
    tree[curr].total_cost += add_cost;
    
    if (L == R) {
        return curr;
    }
    
    int mid = L + (R - L) / 2;
    if (pos <= mid) {
        int left_prev = prev_node ? tree[prev_node].left : 0;
        tree[curr].left = update(left_prev, L, mid, pos, add_portions, add_cost);
    } else {
        int right_prev = prev_node ? tree[prev_node].right : 0;
        tree[curr].right = update(right_prev, mid + 1, R, pos, add_portions, add_cost);
    }
    return curr;
}

// Query range [l, r] using Version r (u) and Version l-1 (v)
pair<long long, long long> query(int u, int v, int L, int R, long long budget) {
    if (!u && !v) return {0, budget};
    
    long long total_p = (u ? tree[u].total_portions : 0) - (v ? tree[v].total_portions : 0);
    if (total_p == 0) return {0, budget};
    
    if (L == R) {
        long long price = L;
        long long can_buy = budget / price;
        long long taken = min(can_buy, total_p);
        return {taken, budget - taken * price};
    }
    
    int mid = L + (R - L) / 2;
    int left_u = u ? tree[u].left : 0;
    int left_v = v ? tree[v].left : 0;
    long long left_portions = (left_u ? tree[left_u].total_portions : 0) - (left_v ? tree[left_v].total_portions : 0);
    long long left_cost = (left_u ? tree[left_u].total_cost : 0) - (left_v ? tree[left_v].total_cost : 0);
    
    if (budget >= left_cost) {
        long long portions = left_portions;
        budget -= left_cost;
        int right_u = u ? tree[u].right : 0;
        int right_v = v ? tree[v].right : 0;
        auto res = query(right_u, right_v, mid + 1, R, budget);
        return {portions + res.first, res.second};
    } else {
        return query(left_u, left_v, L, mid, budget);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> p(n + 1);
    vector<long long> m(n + 1);

    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 1; i <= n; ++i) cin >> m[i];

    // Reserve space for nodes: ~20 nodes per update
    tree.reserve(1 + n * 22);
    tree.push_back({0, 0, 0, 0}); // Dummy node at index 0
    roots.push_back(0);

    // Build persistent versions for each prefix
    for (int i = 1; i <= n; ++i) {
        int prev_root = roots.back();
        int new_root = update(prev_root, 1, MAXV, p[i], m[i], (long long)p[i] * m[i]);
        roots.push_back(new_root);
    }

    // Process queries
    for (int i = 0; i < q; ++i) {
        int l, r;
        long long B;
        cin >> l >> r >> B;
        auto ans = query(roots[r], roots[l - 1], 1, MAXV, B);
        cout << ans.first << " " << ans.second << "\n";
    }

    return 0;
}
