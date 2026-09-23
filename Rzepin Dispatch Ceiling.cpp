#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Edge {
    int to;
    int fuel;
    int turb;
};

struct State {
    ll fuel;
    int node;
    int turb;

    bool operator>(const State& other) const {
        return fuel > other.fuel;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, R;
    cin >> n >> m >> R;

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, fuel, turb;
        cin >> u >> v >> fuel >> turb;

        graph[u].push_back({v, fuel, turb});
    }

    const ll INF = LLONG_MAX / 4;

    // dist[node][turbulence]
    vector<vector<ll>> dist(n + 1, vector<ll>(R + 1, INF));

    priority_queue<State, vector<State>, greater<State>> pq;

    // Home aerodrome = node 1
    dist[1][0] = 0;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        auto [curFuel, u, curTurb] = pq.top();
        pq.pop();

        if (curFuel != dist[u][curTurb])
            continue;

        for (const auto& edge : graph[u]) {
            int newTurb = curTurb + edge.turb;

            if (newTurb > R)
                continue;

            ll newFuel = curFuel + edge.fuel;

            if (newFuel < dist[edge.to][newTurb]) {
                dist[edge.to][newTurb] = newFuel;

                pq.push({
                    newFuel,
                    edge.to,
                    newTurb
                });
            }
        }
    }

    /*
        best[node][t] =
        minimum fuel to reach node with
        turbulence <= t.
    */
    vector<vector<ll>> best(n + 1, vector<ll>(R + 1, INF));

    for (int node = 1; node <= n; node++) {
        ll mn = INF;

        for (int t = 0; t <= R; t++) {
            mn = min(mn, dist[node][t]);
            best[node][t] = mn;
        }
    }

    int q;
    cin >> q;

    while (q--) {
        int dest, tol;
        cin >> dest >> tol;

        if (best[dest][tol] == INF)
            cout << -1 << '\n';
        else
            cout << best[dest][tol] << '\n';
    }

    return 0;
}
