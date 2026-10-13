#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

class DSU {
    vector<int> parent, sz;

public:
    DSU(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
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

        if (a == b) return;

        if (sz[a] < sz[b]) {
            swap(a, b);
        }

        parent[b] = a;
        sz[a] += sz[b];
    }

    int getSize(int x) {
        return sz[find(x)];
    }
};

struct Edge {
    int u, v, cost;
};

struct Query {
    int ward, cap, index;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, E, Q;
    cin >> N >> E >> Q;

    unordered_map<string, int> id;

    for (int i = 0; i < N; i++) {
        string name;
        cin >> name;
        id[name] = i;
    }

    vector<Edge> edges(E);

    for (int i = 0; i < E; i++) {
        string a, b;
        int cost;
        cin >> a >> b >> cost;

        edges[i] = {id[a], id[b], cost};
    }

    vector<Query> queries(Q);

    for (int i = 0; i < Q; i++) {
        string name;
        int cap;
        cin >> name >> cap;

        queries[i] = {id[name], cap, i};
    }

    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) {
             return a.cost < b.cost;
         });

    sort(queries.begin(), queries.end(),
         [](const Query& a, const Query& b) {
             return a.cap < b.cap;
         });

    DSU dsu(N);
    vector<int> answer(Q);
    int j = 0;

    for (const Query& query : queries) {
        while (j < E && edges[j].cost <= query.cap) {
            dsu.unite(edges[j].u, edges[j].v);
            j++;
        }

        answer[query.index] = dsu.getSize(query.ward);
    }

    for (int i = 0; i < Q; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
