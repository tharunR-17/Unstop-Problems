#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);  // Path compression
    }

    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            if (size[rootA] > size[rootB]) {
                parent[rootB] = rootA;
                size[rootA] += size[rootB];
            } else {
                parent[rootA] = rootB;
                size[rootB] += size[rootA];
            }
        }
    }
};

vector<int> maximumWeight(int n, vector<tuple<int, int, int>>& edges, int q, vector<int>& queries) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) < get<2>(b); // Sort edges by weight
    });

    vector<pair<int, int>> sortedQueries(q);
    for (int i = 0; i < q; i++) {
        sortedQueries[i] = {queries[i], i};
    }

    sort(sortedQueries.begin(), sortedQueries.end());  // Sort queries by value

    DSU dsu(n);
    int edgeIndex = 0, pathCount = 0;
    vector<int> result(q);

    for (const auto& query : sortedQueries) {
        int x = query.first, queryIndex = query.second;
        while (edgeIndex < edges.size() && get<2>(edges[edgeIndex]) <= x) {
            int u = get<0>(edges[edgeIndex]);
            int v = get<1>(edges[edgeIndex]);
            int rootU = dsu.find(u);
            int rootV = dsu.find(v);
            if (rootU != rootV) {
                pathCount += dsu.size[rootU] * dsu.size[rootV];
                dsu.unite(u, v);
            }
            edgeIndex++;
        }
        result[queryIndex] = pathCount;
    }

    return result;
}

int main() {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = make_tuple(u, v, w);
    }
    int q;
    cin >> q;
    vector<int> queries(q);
    for (int i = 0; i < q; i++) cin >> queries[i];

    vector<int> result = maximumWeight(n, edges, q, queries);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
