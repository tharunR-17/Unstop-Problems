#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

// DSU / Union-Find
class DSU {
private:
    vector<int> parent, rank_;

public:
    DSU(int n) {
        parent.resize(n + 1);
        rank_.resize(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (rank_[a] < rank_[b]) {
            swap(a, b);
        }

        parent[b] = a;

        if (rank_[a] == rank_[b]) {
            rank_[a]++;
        }
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};

void check_reachability(
    int n,
    int m,
    int q,
    vector<tuple<int, int, int>>& corridors,
    vector<tuple<int, int, int>>& scenarios
) {
    // Sort corridors by cost
    sort(corridors.begin(), corridors.end(),
         [](const auto& x, const auto& y) {
             return get<2>(x) < get<2>(y);
         });

    // Store scenarios along with their original index
    vector<tuple<int, int, int, int>> queries;

    for (int i = 0; i < q; i++) {
        int a, b, budget;
        tie(a, b, budget) = scenarios[i];

        queries.push_back({a, b, budget, i});
    }

    // Sort scenarios by budget
    sort(queries.begin(), queries.end(),
         [](const auto& x, const auto& y) {
             return get<2>(x) < get<2>(y);
         });

    DSU dsu(n);

    vector<string> answer(q);

    int edgeIndex = 0;

    // Process scenarios from smallest budget to largest
    for (auto& query : queries) {

        int a = get<0>(query);
        int b = get<1>(query);
        int budget = get<2>(query);
        int originalIndex = get<3>(query);

        // Add all affordable corridors
        while (edgeIndex < m &&
               get<2>(corridors[edgeIndex]) <= budget) {

            int u = get<0>(corridors[edgeIndex]);
            int v = get<1>(corridors[edgeIndex]);

            dsu.unite(u, v);

            edgeIndex++;
        }

        // Check connectivity
        if (dsu.connected(a, b)) {
            answer[originalIndex] = "YES";
        } else {
            answer[originalIndex] = "NO";
        }
    }

    // Print answers in original query order
    for (int i = 0; i < q; i++) {
        cout << answer[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<tuple<int, int, int>> corridors(m);

    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;

        corridors[i] = make_tuple(u, v, cost);
    }

    vector<tuple<int, int, int>> scenarios(q);

    for (int i = 0; i < q; i++) {
        int a, b, budget;
        cin >> a >> b >> budget;

        scenarios[i] = make_tuple(a, b, budget);
    }

    check_reachability(n, m, q, corridors, scenarios);

    return 0;
}
