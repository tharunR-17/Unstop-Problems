#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;


class DSU {
public:
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n + 1);
        rankv.resize(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rankv[a] < rankv[b])
            swap(a, b);

        parent[b] = a;

        if (rankv[a] == rankv[b])
            rankv[a]++;

        return true;
    }
};

vector<int> compute_worst_corridor(int n, int m, vector<tuple<int, int, int>> &corridors, int q, vector<pair<int, int>> &queries) {
   
    // 1. Sort edges by weight
    sort(corridors.begin(), corridors.end(),
        [](const auto &a, const auto &b) {
            return get<2>(a) < get<2>(b);
        }
    );
      // 2. Build MST using Kruskal
    DSU dsu(n);

    vector<vector<pair<int, int>>> tree(n + 1);

    for (auto [u, v, w] : corridors) {

        if (dsu.unite(u, v)) {

            tree[u].push_back({v, w});
            tree[v].push_back({u, w});
        }
    }
      // 3. Binary Lifting setup

    int LOG = 1;

    while ((1 << LOG) <= n)
        LOG++;

    vector<vector<int>> up(LOG, vector<int>(n + 1));
    vector<vector<int>> mx(LOG, vector<int>(n + 1));

    vector<int> depth(n + 1, -1);

    // 4. DFS/BFS to fill parent and edge maximum

    for (int start = 1; start <= n; start++) {

        if (depth[start] != -1)
            continue;

        depth[start] = 0;
        up[0][start] = 0;
        mx[0][start] = 0;

        queue<int> qu;
        qu.push(start);

        while (!qu.empty()) {

            int u = qu.front();
            qu.pop();

            for (auto [v, w] : tree[u]) {

                if (depth[v] != -1)
                    continue;

                depth[v] = depth[u] + 1;

                up[0][v] = u;
                mx[0][v] = w;

                qu.push(v);
            }
        }
    }
      // 5. Build Binary Lifting table
     for (int j = 1; j < LOG; j++) {

        for (int v = 1; v <= n; v++) {

            int ancestor = up[j - 1][v];

            up[j][v] = up[j - 1][ancestor];

            mx[j][v] = max(
                mx[j - 1][v],
                mx[j - 1][ancestor]
            );
        }
    }
     // 6. Answer queries
    vector<int> results(q, -1);

    for (int qi = 0; qi < q; qi++) {

        auto [a, b] = queries[qi];

        // Different connected components
        if (depth[a] == -1 || depth[b] == -1) {
            results[qi] = -1;
            continue;
        }

        // Since we started BFS separately for each component,
        // compare their DSU roots.
        if (dsu.find(a) != dsu.find(b)) {
            results[qi] = -1;
            continue;
        }

        int answer = 0;

        // Make a deeper than b
        if (depth[a] < depth[b])
            swap(a, b);

        int diff = depth[a] - depth[b];

        // Lift a to same depth as b
        for (int j = LOG - 1; j >= 0; j--) {

            if (diff & (1 << j)) {

                answer = max(answer, mx[j][a]);

                a = up[j][a];
            }
        }

        // Already same node
        if (a == b) {
            results[qi] = answer;
            continue;
        }

        // Lift both together
        for (int j = LOG - 1; j >= 0; j--) {

            if (up[j][a] != up[j][b]) {

                answer = max(answer, mx[j][a]);
                answer = max(answer, mx[j][b]);

                a = up[j][a];
                b = up[j][b];
            }
        }

        // Include edges connecting both to LCA
        answer = max(answer, mx[0][a]);
        answer = max(answer, mx[0][b]);

        results[qi] = answer;
    }

    return results;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> corridors(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        corridors[i] = make_tuple(u, v, w);
    }

    int q;
    cin >> q;

    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        queries[i] = make_pair(a, b);
    }

    vector<int> results = compute_worst_corridor(n, m, corridors, q, queries);

    for (const int &result : results) {
        cout << result << endl;
    }

    return 0;
}
