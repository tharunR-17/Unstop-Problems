#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <numeric>

using namespace std;

class DSU {
public:
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
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

        // Keep the larger component as root
        if (sz[a] < sz[b])
            swap(a, b);

        parent[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

void process_entries(
    int n,
    int m,
    const vector<int>& chamber_values,
    const vector<pair<string, vector<int>>>& entries,
    vector<pair<int, int>>& results
) {
    DSU dsu(n);

    /*
        relics[root] contains:
        {-value, chamber_number}

        Example:
        value = 30, chamber = 3
        stored as {-30, 3}

        Smaller pair = higher value.
        If values are equal, smaller chamber number comes first.
    */
    vector<set<pair<int, int>>> relics(n + 1);

    // Initially every chamber is its own component
    for (int i = 1; i <= n; i++) {
        if (chamber_values[i - 1] > 0) {
            relics[i].insert({-chamber_values[i - 1], i});
        }
    }

    for (const auto& entry : entries) {
        string type = entry.first;

        if (type == "LINK") {
            int u = entry.second[0];
            int v = entry.second[1];

            int ru = dsu.find(u);
            int rv = dsu.find(v);

            if (ru == rv)
                continue;

            // Merge the DSU components.
            // unite() makes the larger component the root.
            int oldRu = ru;
            int oldRv = rv;

            dsu.unite(ru, rv);

            int newRoot = dsu.find(ru);

            // Merge relic sets into the new root.
            if (newRoot == oldRu) {
                relics[oldRu].insert(
                    relics[oldRv].begin(),
                    relics[oldRv].end()
                );
                relics[oldRv].clear();
            } else {
                relics[oldRv].insert(
                    relics[oldRu].begin(),
                    relics[oldRu].end()
                );
                relics[oldRu].clear();
            }
        }

        else if (type == "CLAIM") {
            int x = entry.second[0];

            int root = dsu.find(x);

            if (relics[root].empty()) {
                results.push_back({-1, -1});
            } else {
                // Best relic
                auto it = relics[root].begin();

                int value = -it->first;
                int chamber = it->second;

                results.push_back({chamber, value});

                // Relic is permanently claimed
                relics[root].erase(it);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> chamber_values(n);

    for (int i = 0; i < n; i++) {
        cin >> chamber_values[i];
    }

    vector<pair<string, vector<int>>> entries(m);

    for (int i = 0; i < m; i++) {
        string entry_type;
        cin >> entry_type;

        entries[i].first = entry_type;

        if (entry_type == "LINK") {
            int u, v;
            cin >> u >> v;
            entries[i].second = {u, v};
        }
        else if (entry_type == "CLAIM") {
            int x;
            cin >> x;
            entries[i].second = {x};
        }
    }

    vector<pair<int, int>> results;

    process_entries(
        n,
        m,
        chamber_values,
        entries,
        results
    );

    for (const auto& result : results) {
        if (result.first == -1) {
            cout << "EMPTY\n";
        }
        else {
            cout << result.first << " "
                 << result.second << "\n";
        }
    }

    return 0;
}
