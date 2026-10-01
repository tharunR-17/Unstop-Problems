#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent;
    vector<int> sz;
    vector<long long> mx;

    DSU(int n, vector<long long>& rating) {
        parent.resize(n);
        sz.resize(n, 1);
        mx = rating;

        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if(parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if(a == b)
            return;

        // Union by size
        if(sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        mx[a] = max(mx[a], mx[b]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<string, int> id;
    vector<long long> rating(n);

    for(int i = 0; i < n; i++) {
        string name;
        cin >> name >> rating[i];

        id[name] = i;
    }

    DSU dsu(n, rating);

    int q;
    cin >> q;

    while(q--) {
        string operation;
        cin >> operation;

        if(operation == "LINK") {
            string x, y;
            cin >> x >> y;

            dsu.unite(id[x], id[y]);
        }

        else if(operation == "BOOST") {
            string x;
            long long v;

            cin >> x >> v;

            int node = id[x];

            dsu.mx[dsu.find(node)] =
                max(dsu.mx[dsu.find(node)], rating[node] + v);

            rating[node] += v;
        }

        else if(operation == "QUERY") {
            string x;
            cin >> x;

            int node = id[x];
            int root = dsu.find(node);

            cout << dsu.mx[root] << '\n';
        }
    }

    return 0;
}
