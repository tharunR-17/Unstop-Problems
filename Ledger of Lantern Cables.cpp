#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 400005;
const int LOG = 20;

int dsu[MAXN];
int W[MAXN];
int Sz[MAXN];
int par[MAXN];
vector<int> adj[MAXN];

int up[MAXN][LOG];
int depth[MAXN];
int tree_root[MAXN];

// Disjoint Set Union (DSU) Find
int find_set(int v) {
    return v == dsu[v] ? v : (dsu[v] = find_set(dsu[v]));
}

// Depth First Search to setup Binary Lifting arrays
void dfs(int u, int p) {
    up[u][0] = p;
    depth[u] = depth[p] + 1;
    tree_root[u] = (p == 0) ? u : tree_root[p];
    
    for (int i = 1; i < LOG; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    
    for (int v : adj[u]) {
        dfs(v, u);
    }
}

// Lowest Common Ancestor (LCA) using Binary Lifting
int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    for (int i = 1; i <= 2 * n; i++) {
        dsu[i] = i;
    }

    for (int i = 1; i <= n; i++) {
        Sz[i] = 1;
        W[i] = 0;
    }

    int node_cnt = n;
    
    // Construct Kruskal Reconstruction Tree
    for (int i = 0; i < m; i++) {
        int d, u, v;
        cin >> d >> u >> v;
        
        int ru = find_set(u);
        int rv = find_set(v);
        
        if (ru != rv) {
            node_cnt++;
            W[node_cnt] = d;
            Sz[node_cnt] = Sz[ru] + Sz[rv];
            dsu[ru] = node_cnt;
            dsu[rv] = node_cnt;
            
            adj[node_cnt].push_back(ru);
            adj[node_cnt].push_back(rv);
            par[ru] = node_cnt;
            par[rv] = node_cnt;
        }
    }

    // Process disjoint trees in the constructed forest
    for (int i = 1; i <= node_cnt; i++) {
        if (par[i] == 0) {
            dfs(i, 0);
        }
    }

    // Evaluate queries
    for (int i = 0; i < q; i++) {
        int u, v, k;
        cin >> u >> v >> k;

        if (tree_root[u] != tree_root[v]) {
            cout << -1 << (i == q - 1 ? "" : " ");
        } else {
            int lca = get_lca(u, v);
            int curr = lca;
            
            // Go up to find the lowest ancestor with cluster size < k
            for (int j = LOG - 1; j >= 0; j--) {
                if (up[curr][j] != 0 && Sz[up[curr][j]] < k) {
                    curr = up[curr][j];
                }
            }
            
            // Hop 1 final parent boundary layer jump if the max-size ceiling ancestor fell short
            if (Sz[curr] < k) {
                curr = up[curr][0];
            }
            
            if (curr == 0 || Sz[curr] < k) {
                cout << -1 << (i == q - 1 ? "" : " ");
            } else {
                cout << W[curr] << (i == q - 1 ? "" : " ");
            }
        }
    }
    cout << "\n";
    return 0;
}
