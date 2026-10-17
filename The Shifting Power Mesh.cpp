#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

class DSU {
public:
    vector<int> parent, sz;
    vector<multiset<pair<int, int>>> active;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        active.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }

        if (sz[a] < sz[b]) {
            swap(a, b);
        }

        parent[b] = a;
        sz[a] += sz[b];

        if (active[a].size() < active[b].size()) {
            swap(active[a], active[b]);
        }

        active[a].insert(active[b].begin(), active[b].end());
        active[b].clear();
    }

    void turnOn(int s, int capacity) {
        int root = find(s);
        active[root].insert({capacity, s});
    }

    void turnOff(int s, int capacity) {
        int root = find(s);
        active[root].erase({capacity, s});
    }

    void query(int s) {
        int root = find(s);

        if (active[root].empty()) {
            cout << "-1 -1\n";
            return;
        }

        auto it = active[root].rbegin();
        cout << it->first << " " << it->second << "\n";
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> capacity(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> capacity[i];
    }

    DSU dsu(n);

    int m;
    cin >> m;

    while (m--) {
        string operation;
        cin >> operation;

        if (operation == "LINK") {
            int a, b;
            cin >> a >> b;
            dsu.unite(a, b);
        }
        else if (operation == "ON") {
            int s;
            cin >> s;
            dsu.turnOn(s, capacity[s]);
        }
        else if (operation == "OFF") {
            int s;
            cin >> s;
            dsu.turnOff(s, capacity[s]);
        }
        else if (operation == "QUERY") {
            int s;
            cin >> s;
            dsu.query(s);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
