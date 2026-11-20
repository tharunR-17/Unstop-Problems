#include <iostream>
#include <vector>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

using ordered_set = tree<
    pair<ll, int>,
    null_type,
    less<pair<ll, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

struct DSU {
    vector<int> parent, sz;
    vector<ll> sum;

    ordered_set components;
    int componentCount;

    DSU(int n, const vector<ll>& capacity) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        sum.resize(n + 1);

        componentCount = n;

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            sum[i] = capacity[i];

            components.insert({sum[i], i});
        }
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);

        // Already in the same component.
        if (u == v)
            return;

        // Union by size.
        if (sz[u] < sz[v])
            swap(u, v);

        // Remove old component capacities.
        components.erase({sum[u], u});
        components.erase({sum[v], v});

        // Merge smaller component into larger.
        parent[v] = u;
        sz[u] += sz[v];
        sum[u] += sum[v];

        // Insert updated component capacity.
        components.insert({sum[u], u});

        componentCount--;
    }

    pair<int, ll> getAnswer(int k) {
        if (k > componentCount)
            return {componentCount, 0};

        // K-th largest = (componentCount - k)-th smallest.
        auto it = components.find_by_order(componentCount - k);

        return {componentCount, it->first};
    }
};

void solve() {
    int M, C, S;
    cin >> M >> C >> S;

    vector<ll> capacity(M + 1);

    for (int i = 1; i <= M; i++) {
        cin >> capacity[i];
    }

    vector<pair<int, int>> edges(C + 1);

    for (int i = 1; i <= C; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<pair<int, int>> queries(S + 1);
    vector<bool> removed(C + 1, false);

    for (int i = 1; i <= S; i++) {
        int c, k;
        cin >> c >> k;

        queries[i] = {c, k};
        removed[c] = true;
    }

    // Build the graph after all deletions.
    DSU dsu(M, capacity);

    for (int i = 1; i <= C; i++) {
        if (!removed[i]) {
            dsu.unite(edges[i].first, edges[i].second);
        }
    }

    vector<pair<int, ll>> ans(S + 1);

    // Process deletion events in reverse order.
    for (int i = S; i >= 1; i--) {

        int cable = queries[i].first;
        int k = queries[i].second;

        // Current graph represents the state
        // immediately after event i.
        ans[i] = dsu.getAnswer(k);

        // Restore the deleted cable.
        int u = edges[cable].first;
        int v = edges[cable].second;

        dsu.unite(u, v);
    }

    // Print answers in original event order.
    for (int i = 1; i <= S; i++) {
        cout << ans[i].first << " "
             << ans[i].second << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
