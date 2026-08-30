#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = (1LL << 62);

struct Edge {
    int to;
    ll first;
    ll freq;
    ll dur;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, S, D;
    cin >> n >> m >> S >> D;

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll first, freq, dur;

        cin >> u >> v >> first >> freq >> dur;

        graph[u].push_back({
            v,
            first,
            freq,
            dur
        });
    }

    vector<ll> dist(n + 1, INF);

    // {earliest arrival time, station}
    priority_queue<
        pair<ll, int>,
        vector<pair<ll, int>>,
        greater<pair<ll, int>>
    > pq;

    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty()) {

        auto [currentTime, u] = pq.top();
        pq.pop();

        // Outdated priority queue entry
        if (currentTime != dist[u])
            continue;

        // Earliest possible arrival at D is finalized
        if (u == D)
            break;

        for (const Edge &edge : graph[u]) {

            ll departure;

            // -----------------------------
            // Case 1:
            // First train hasn't left yet
            // -----------------------------
            if (currentTime <= edge.first) {

                departure = edge.first;
            }

            // -----------------------------
            // Case 2:
            // One-time train already missed
            // -----------------------------
            else if (edge.freq == 0) {

                continue;
            }

            // -----------------------------
            // Case 3:
            // Find next periodic departure
            // -----------------------------
            else {

                ll diff = currentTime - edge.first;

                ll k =
                    (diff + edge.freq - 1)
                    / edge.freq;

                departure =
                    edge.first + k * edge.freq;
            }

            ll arrival =
                departure + edge.dur;

            // Normal Dijkstra relaxation
            if (arrival < dist[edge.to]) {

                dist[edge.to] = arrival;

                pq.push({
                    arrival,
                    edge.to
                });
            }
        }
    }

    if (dist[D] == INF)
        cout << -1 << '\n';
    else
        cout << dist[D] << '\n';

    return 0;
}
