#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
public:
    int n;
    vector<int> fw;

    FenwickTree(int size) {
        n = size;
        fw.assign(n + 1, 0);
    }

    void update(int i, int delta) {
        while (i <= n) {
            fw[i] += delta;
            i += i & -i;
        }
    }

    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += fw[i];
            i -= i & -i;
        }
        return sum;
    }

    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void dfs(int u, int parent, vector<vector<int>>& tree, vector<int>& in_time, vector<int>& out_time, vector<int>& euler, int& timer) {
    in_time[u] = timer;
    euler[timer] = u;
    timer++;
    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs(v, u, tree, in_time, out_time, euler, timer);
    }
    out_time[u] = timer;
}

vector<string> process_queries(int N, int q, vector<pair<int, int>>& edges, vector<int>& values, vector<vector<int>>& queries) {
    vector<vector<int>> tree(N + 1);
    for (auto& edge : edges) {
        int u = edge.first, v = edge.second;
        if (1 <= u && u <= N && 1 <= v && v <= N) {
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
    }
    
    vector<int> in_time(N + 1, 0), out_time(N + 1, 0), euler(N + 1, 0);
    int timer = 1;
    if (N >= 1) dfs(1, 0, tree, in_time, out_time, euler, timer);
    
    FenwickTree bit(N);
    vector<int> par(N + 1);
    for (int node = 1; node <= N; node++) {
        par[node] = (values[node - 1] % 2 == 0) ? 0 : 1;
        if (par[node] == 0) bit.update(in_time[node], 1);
    }
    
    vector<string> results;
    for (auto& query : queries) {
        int t = query[0], node = query[1];
        if (node < 1 || node > N) {
            if (t == 1) continue;
            else {
                results.push_back("YES");
                continue;
            }
        }
        if (t == 1) {
            int x = query[2];
            int new_parity = (x % 2 == 0) ? 0 : 1;
            if (new_parity != par[node]) {
                int pos = in_time[node];
                if (new_parity == 0) bit.update(pos, 1);
                else bit.update(pos, -1);
                par[node] = new_parity;
            }
        } else {
            int l = in_time[node], r = out_time[node] - 1;
            int even_count = bit.range_query(l, r);
            int total = r - l + 1;
            int odd_count = total - even_count;
            if (min(even_count, odd_count) <= 1) results.push_back("YES");
            else results.push_back("NO");
        }
    }
    return results;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, q;
    cin >> N >> q;
    
    vector<pair<int, int>> edges(N - 1);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }
    
    vector<int> values(N);
    for (int i = 0; i < N; i++) cin >> values[i];
    
    vector<vector<int>> queries(q);
    for (int i = 0; i < q; i++) {
        int t, node;
        cin >> t >> node;
        if (t == 1) {
            int x;
            cin >> x;
            queries[i] = {t, node, x};
        } else {
            queries[i] = {t, node};
        }
    }
    
    vector<string> results = process_queries(N, q, edges, values, queries);
    for (const string& res : results) cout << res << "\n";
    
    return 0;
}
