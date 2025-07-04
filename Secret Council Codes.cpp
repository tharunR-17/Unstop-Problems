#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int get(int x) {
        if (parent[x] != x) parent[x] = get(parent[x]);
        return parent[x];
    }
    void merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return;
        if (rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        rank[x] += rank[y];
    }
};

int calculateXorBasis(const vector<int>& elements) {
    vector<int> basis;
    for (int val : elements) {
        for (int b : basis) val = min(val, val ^ b);
        if (val) basis.push_back(val);
    }
    return (int)basis.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> values(n);
    for (int i = 0; i < n; ++i) cin >> values[i];

    UnionFind uf(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        uf.merge(a - 1, b - 1);
    }

    unordered_map<int, vector<int>> components;
    for (int i = 0; i < n; ++i) {
        int root = uf.get(i);
        components[root].push_back(values[i]);
    }

    long long result = 0;
    for (auto& entry : components) {
        int basisSize = calculateXorBasis(entry.second);
        result += (1LL << basisSize);
    }

    cout << result << '\n';
    return 0;
}
