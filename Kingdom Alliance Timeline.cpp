#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
};

struct Query {
    int u, v, idx;
};

struct DSURollback {
    vector<int> p, sz;
    vector<pair<int,int>> st;

    DSURollback(int n) {
        p.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        while (p[x] != x) x = p[x];
        return x;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            st.push_back({-1, -1});
            return;
        }
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        st.push_back({a, b});
    }

    int snapshot() {
        return st.size();
    }

    void rollback(int snap) {
        while ((int)st.size() > snap) {
            auto [a, b] = st.back();
            st.pop_back();
            if (a == -1) continue;
            sz[a] -= sz[b];
            p[b] = b;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int M;
    cin >> M;

    vector<tuple<int,int,int,int>> edges(M);
    vector<int> coords;

    for (int i = 0; i < M; i++) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        edges[i] = {u, v, l, r};
        coords.push_back(l);
        coords.push_back(r + 1);
    }

    int Q;
    cin >> Q;

    vector<tuple<int,int,int>> queries(Q);

    for (int i = 0; i < Q; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        queries[i] = {u, v, t};
        coords.push_back(t);
    }

    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    int K = coords.size();

    vector<vector<Edge>> seg(4 * K + 5);
    vector<vector<Query>> ask(4 * K + 5);

    auto addEdge = [&](auto &&self, int node, int l, int r, int ql, int qr, Edge e) -> void {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            seg[node].push_back(e);
            return;
        }
        int mid = (l + r) >> 1;
        self(self, node << 1, l, mid, ql, qr, e);
        self(self, node << 1 | 1, mid + 1, r, ql, qr, e);
    };

    auto addQuery = [&](auto &&self, int node, int l, int r, int pos, Query q) -> void {
        if (l == r) {
            ask[node].push_back(q);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) self(self, node << 1, l, mid, pos, q);
        else self(self, node << 1 | 1, mid + 1, r, pos, q);
    };

    for (auto &[u, v, l, r] : edges) {
        int L = lower_bound(coords.begin(), coords.end(), l) - coords.begin();
        int R = lower_bound(coords.begin(), coords.end(), r + 1) - coords.begin() - 1;
        if (L <= R)
            addEdge(addEdge, 1, 0, K - 1, L, R, {u, v});
    }

    for (int i = 0; i < Q; i++) {
        auto [u, v, t] = queries[i];
        int pos = lower_bound(coords.begin(), coords.end(), t) - coords.begin();
        addQuery(addQuery, 1, 0, K - 1, pos, {u, v, i});
    }

    vector<string> ans(Q);
    DSURollback dsu(N);

    auto dfs = [&](auto &&self, int node, int l, int r) -> void {
        int snap = dsu.snapshot();

        for (auto &e : seg[node])
            dsu.unite(e.u, e.v);

        if (l == r) {
            for (auto &q : ask[node]) {
                ans[q.idx] = (dsu.find(q.u) == dsu.find(q.v)) ? "YES" : "NO";
            }
        } else {
            int mid = (l + r) >> 1;
            self(self, node << 1, l, mid);
            self(self, node << 1 | 1, mid + 1, r);
        }

        dsu.rollback(snap);
    };

    dfs(dfs, 1, 0, K - 1);

    for (auto &x : ans)
        cout << x << '\n';

    return 0;
}
