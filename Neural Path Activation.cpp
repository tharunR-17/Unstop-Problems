#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree, lazy;

    SegmentTree(int size) {
        n = 1;
        while(n < size) n <<= 1;
        tree.assign(2*n, 0);
        lazy.assign(2*n, 0);
    }

    void push(int idx, int l, int r) {
        if (lazy[idx]) {
            tree[idx] = (r - l + 1) - tree[idx];
            if (l != r) {
                lazy[idx*2] ^= 1;
                lazy[idx*2+1] ^= 1;
            }
            lazy[idx] = 0;
        }
    }

    void update(int idx, int l, int r, int ql, int qr) {
        push(idx, l, r);
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            lazy[idx] ^= 1;
            push(idx, l, r);
            return;
        }
        int mid = (l + r)/2;
        update(idx*2, l, mid, ql, qr);
        update(idx*2+1, mid+1, r, ql, qr);
        tree[idx] = tree[idx*2] + tree[idx*2+1];
    }

    int query(int idx, int l, int r, int ql, int qr) {
        push(idx, l, r);
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr) return tree[idx];
        int mid = (l + r)/2;
        return query(idx*2, l, mid, ql, qr) + query(idx*2+1, mid+1, r, ql, qr);
    }
};

struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> size, depth, parent, heavy, head, pos;
    int cur_pos;

    HLD(int n): n(n) {
        adj.resize(n+1);
        size.resize(n+1);
        depth.resize(n+1);
        parent.resize(n+1);
        heavy.assign(n+1, -1);
        head.resize(n+1);
        pos.resize(n+1);
        cur_pos = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p) {
        size[u] = 1;
        int max_subtree = 0;
        for (int v : adj[u]) {
            if (v != p) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                dfs(v, u);
                size[u] += size[v];
                if (size[v] > max_subtree) {
                    max_subtree = size[v];
                    heavy[u] = v;
                }
            }
        }
    }

    void decompose(int u, int h) {
        head[u] = h;
        pos[u] = cur_pos++;
        if (heavy[u] != -1) decompose(heavy[u], h);
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u]) decompose(v, v);
        }
    }

    void updatePath(int u, int v, SegmentTree &segtree) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            segtree.update(1, 0, n - 1, pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (pos[u] + 1 <= pos[v])
            segtree.update(1, 0, n - 1, pos[u] + 1, pos[v]);
    }

    int queryPath(int u, int v, SegmentTree &segtree) {
        int res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            res += segtree.query(1, 0, n - 1, pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        if (pos[u] + 1 <= pos[v])
            res += segtree.query(1, 0, n - 1, pos[u] + 1, pos[v]);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    HLD hld(n);
    for (int i = 0; i < n - 1; i++) {
        int a,b; cin >> a >> b;
        hld.addEdge(a,b);
    }
    hld.dfs(1,-1);
    hld.decompose(1,1);
    SegmentTree segtree(n);

    int q; cin >> q;
    while(q--) {
        int t,u,v; cin >> t >> u >> v;
        if (t == 1) {
            hld.updatePath(u,v,segtree);
        } else {
            cout << hld.queryPath(u,v,segtree) << "\n";
        }
    }
    return 0;
}
