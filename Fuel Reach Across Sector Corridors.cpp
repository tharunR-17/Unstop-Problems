#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    int id;
    int t;
    int a;
};

struct Edge {
    int u, v;
};

struct Permit {
    int u, v, s, e;
};

// DSU with Rollback support
struct RollbackDSU {
    vector<int> parent;
    vector<int> sz;
    vector<long long> fuel;
    
    struct State {
        int u, v;
        int sz_v;
        long long fuel_v;
    };
    vector<State> history;

    RollbackDSU(int n, const vector<long long>& initial_fuel) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        fuel.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            fuel[i] = initial_fuel[i - 1];
        }
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return find_set(parent[v]); // no path compression
    }

    void unite(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (sz[a] > sz[b])
                swap(a, b);
            
            // We attach a to b
            history.push_back({a, b, sz[b], fuel[b]});
            
            parent[a] = b;
            sz[b] += sz[a];
            fuel[b] += fuel[a];
        } else {
            // Push dummy state to maintain consistent rollback count
            history.push_back({-1, -1, -1, -1});
        }
    }

    void rollback() {
        State st = history.back();
        history.pop_back();
        if (st.u != -1) {
            parent[st.u] = st.u;
            sz[st.v] = st.sz_v;
            fuel[st.v] = st.fuel_v;
        }
    }
};

vector<vector<Edge>> tree;
vector<long long> ans_sz, ans_fuel;
vector<vector<pair<int, int>>> leaf_queries; // stores {start_node, query_id}

void add_edge(int node, int l, int r, int ql, int qr, Edge e) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree[node].push_back(e);
        return;
    }
    int mid = l + (r - l) / 2;
    add_edge(2 * node, l, mid, ql, qr, e);
    add_edge(2 * node + 1, mid + 1, r, ql, qr, e);
}

void dfs(int node, int l, int r, RollbackDSU& dsu) {
    for (const Edge& e : tree[node]) {
        dsu.unite(e.u, e.v);
    }
    
    if (l == r) {
        for (const auto& q : leaf_queries[l]) {
            int root = dsu.find_set(q.first);
            ans_sz[q.second] = dsu.sz[root];
            ans_fuel[q.second] = dsu.fuel[root];
        }
    } else {
        int mid = l + (r - l) / 2;
        dfs(2 * node, l, mid, dsu);
        dfs(2 * node + 1, mid + 1, r, dsu);
    }
    
    for (int i = 0; i < tree[node].size(); ++i) {
        dsu.rollback();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A, K, Q;
    if (!(cin >> A >> K >> Q)) return 0;

    vector<long long> f(A);
    for (int i = 0; i < A; ++i) {
        cin >> f[i];
    }

    vector<Permit> permits(K);
    for (int i = 0; i < K; ++i) {
        cin >> permits[i].u >> permits[i].v >> permits[i].s >> permits[i].e;
    }

    vector<Query> queries(Q);
    vector<int> times;
    for (int i = 0; i < Q; ++i) {
        queries[i].id = i;
        cin >> queries[i].t >> queries[i].a;
        times.push_back(queries[i].t);
    }

    sort(times.begin(), times.end());
    times.erase(unique(times.begin(), times.end()), times.end());
    
    int M = times.size();
    if (M == 0) return 0;

    tree.resize(4 * M);
    leaf_queries.resize(M);
    
    for (int i = 0; i < Q; ++i) {
        int idx = lower_bound(times.begin(), times.end(), queries[i].t) - times.begin();
        leaf_queries[idx].push_back({queries[i].a, queries[i].id});
    }

    for (int i = 0; i < K; ++i) {
        int L = lower_bound(times.begin(), times.end(), permits[i].s) - times.begin();
        int R = upper_bound(times.begin(), times.end(), permits[i].e) - times.begin() - 1;
        if (L <= R) {
            add_edge(1, 0, M - 1, L, R, {permits[i].u, permits[i].v});
        }
    }

    ans_sz.resize(Q);
    ans_fuel.resize(Q);
    
    RollbackDSU dsu(A, f);
    dfs(1, 0, M - 1, dsu);

    for (int i = 0; i < Q; ++i) {
        cout << ans_sz[i] << " " << ans_fuel[i] << "\n";
    }

    return 0;
}
