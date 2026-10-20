#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Structure to represent a candidate tunnel
struct Edge {
    int u, v;
    long long cost;
    bool operator<(const Edge& other) const {
        return cost < other.cost; // Sort by cost ascending
    }
};

// Disjoint Set Union (DSU) to manage connected components
struct DSU {
    vector<int> parent;
    vector<int> size;
    vector<int> min_zone;

    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        min_zone.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            min_zone[i] = i; // Track the smallest zone index in the cluster
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            // Union by size
            if (size[root_i] < size[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
            // Maintain the smallest zone number in the cluster for tie-breaking
            min_zone[root_i] = min(min_zone[root_i], min_zone[root_j]);
            return true;
        }
        return false;
    }
};

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> categories(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> categories[i];
    }

    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    // Step 1: Sort candidate tunnels strictly in order of increasing cost
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    long long total_cost = 0;

    // Step 2: Build the Minimum Spanning Forest
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            total_cost += edge.cost;
        }
    }

    // Step 3: Find the largest cluster (tie-breaker: smallest zone numbering)
    int best_root = -1;
    int max_size = -1;
    int best_min_zone = n + 1;

    for (int i = 1; i <= n; ++i) {
        int root = dsu.find(i);
        if (root == i) { // Check only component roots
            if (dsu.size[root] > max_size) {
                max_size = dsu.size[root];
                best_min_zone = dsu.min_zone[root];
                best_root = root;
            } else if (dsu.size[root] == max_size) {
                if (dsu.min_zone[root] < best_min_zone) {
                    best_min_zone = dsu.min_zone[root];
                    best_root = root;
                }
            }
        }
    }

    // Step 4: Count artifact category frequencies within the best cluster
    map<int, int> category_counts;
    for (int i = 1; i <= n; ++i) {
        if (dsu.find(i) == best_root) {
            category_counts[categories[i]]++;
        }
    }

    // Step 5: Find the most frequent artifact category (tie-breaker: smaller category code)
    int most_freq_category = -1;
    int max_freq = -1;

    for (const auto& pair : category_counts) {
        int cat = pair.first;
        int freq = pair.second;
        if (freq > max_freq) {
            max_freq = freq;
            most_freq_category = cat;
        } else if (freq == max_freq) {
            if (cat < most_freq_category) {
                most_freq_category = cat;
            }
        }
    }

    // Print final expected output
    cout << total_cost << " " << max_size << " " << most_freq_category << " " << max_freq << "\n";

    return 0;
}
