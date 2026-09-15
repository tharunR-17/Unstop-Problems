#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int n;
    vector<int> tree;

public:
    SegmentTree(int n) : n(n) {
        tree.assign(4 * n + 5, 0);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            // Position 1 belongs to root, which has no incoming edge.
            // All other nodes represent one initially active edge.
            tree[node] = (l == 1 ? 0 : 1);
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int node, int l, int r, int idx) {
        if (l == r) {
            tree[node] ^= 1;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx);
        else
            update(node * 2 + 1, mid + 1, r, idx);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;

        if (ql <= l && r <= qr)
            return tree[node];

        int mid = (l + r) / 2;

        return query(node * 2, l, mid, ql, qr) +
               query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    void toggle(int idx) {
        update(1, 1, n, idx);
    }

    int query(int l, int r) {
        if (l > r)
            return 0;

        return query(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /*
        -----------------------------------------
        Step 1: Root the tree at node 1
        -----------------------------------------
    */

    vector<int> parent(n + 1, 0);
    vector<int> depth(n + 1, 0);
    vector<int> order;

    order.reserve(n);

    // Iterative DFS
    stack<int> st;
    st.push(1);
    parent[1] = -1;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        order.push_back(u);

        for (int v : adj[u]) {
            if (v == parent[u])
                continue;

            parent[v] = u;
            depth[v] = depth[u] + 1;
            st.push(v);
        }
    }

    /*
        -----------------------------------------
        Step 2: Calculate subtree sizes
                 and heavy child
        -----------------------------------------
    */

    vector<int> subtree(n + 1, 1);
    vector<int> heavy(n + 1, -1);

    // Process nodes bottom-up
    for (int i = n - 1; i > 0; i--) {
        int u = order[i];

        int bestSize = 0;

        for (int v : adj[u]) {
            if (parent[v] != u)
                continue;

            subtree[u] += subtree[v];

            if (subtree[v] > bestSize) {
                bestSize = subtree[v];
                heavy[u] = v;
            }
        }
    }

    /*
        -----------------------------------------
        Step 3: Heavy-Light Decomposition
        -----------------------------------------
    */

    vector<int> head(n + 1);
    vector<int> pos(n + 1);

    int timer = 0;

    /*
        We process every heavy chain iteratively.
    */

    stack<pair<int, int>> chains;

    chains.push({1, 1});

    while (!chains.empty()) {
        auto [start, chainHead] = chains.top();
        chains.pop();

        int u = start;

        while (u != -1) {
            head[u] = chainHead;
            pos[u] = ++timer;

            // Light children start new chains
            for (int v : adj[u]) {
                if (parent[v] == u && v != heavy[u]) {
                    chains.push({v, v});
                }
            }

            u = heavy[u];
        }
    }

    /*
        -----------------------------------------
        Step 4: Segment Tree
        -----------------------------------------
        
        Important:
        
        Edge (parent[v], v) is represented by node v.

        Therefore:
        
        node v = 1  => edge parent[v] -> v is ON
        node v = 0  => edge parent[v] -> v is OFF

        Root node 1 has no incoming edge, so its value is 0.
    */

    SegmentTree seg(n);
    seg.build(1, 1, n);

    /*
        -----------------------------------------
        Path Query
        -----------------------------------------
    */

    auto queryPath = [&](int u, int v) {
        int answer = 0;

        while (head[u] != head[v]) {

            // Always move the deeper chain upward
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            /*
                head[u] ... u

                Every node in this range represents
                the edge connecting it to its parent.
            */

            answer += seg.query(pos[head[u]], pos[u]);

            u = parent[head[u]];
        }

        // Same heavy chain now

        if (depth[u] > depth[v])
            swap(u, v);

        /*
            u is now the shallower node.

            The edge represented by u belongs to
            parent[u] -> u, which is NOT part of
            path(u, v).

            So start from pos[u] + 1.
        */

        answer += seg.query(pos[u] + 1, pos[v]);

        return answer;
    };

    /*
        -----------------------------------------
        Process Queries
        -----------------------------------------
    */

    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int v;
            cin >> v;

            // Toggle the edge parent[v] -> v
            seg.toggle(pos[v]);
        }
        else {
            int u, v;
            cin >> u >> v;

            cout << queryPath(u, v) << '\n';
        }
    }

    return 0;
}
