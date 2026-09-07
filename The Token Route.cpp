#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct State {
    ll dist;
    int node;
    int used;

    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

int main() {
    
    int n, m, k, src, dst;
    cin >> n >> m >> k >> src >> dst;

    vector<vector<pair<int, int>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    const ll INF = LLONG_MAX / 4;

    // dist[used][node]
    vector<vector<ll>> dist(k + 1, vector<ll>(n + 1, INF));

    priority_queue<
        State,
        vector<State>,
        greater<State>
    > pq;

    dist[0][src] = 0;
    pq.push({0, src, 0});

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        ll d = cur.dist;
        int u = cur.node;
        int used = cur.used;

        if (d != dist[used][u])
            continue;

        // Early exit:
        // The first time dst is popped, it is globally minimum.
        if (u == dst) {
            cout << d << '\n';
            return 0;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            // Normal traversal
            ll nd = d + w;

            if (nd < dist[used][v]) {
                dist[used][v] = nd;
                pq.push({nd, v, used});
            }

            // Use token
            if (used < k && d < dist[used + 1][v]) {
                dist[used + 1][v] = d;
                pq.push({d, v, used + 1});
            }
        }
    }

    cout << -1 << '\n';

    return 0;
}
