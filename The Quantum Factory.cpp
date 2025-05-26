#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> V(N), K(N);
    for (int i = 0; i < N; ++i) cin >> V[i];
    for (int i = 0; i < N; ++i) cin >> K[i];

    double E;
    cin >> E;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);  // Convert to 0-based index
    }

    // Compute scaling factors
    vector<double> scale(N);
    for (int i = 0; i < N; ++i) {
        int mod_val = (K[i] * V[i]) % 100;
        scale[i] = 1.0 - (mod_val / 100.0);
    }

    vector<double> max_energy(N, 0.0);
    max_energy[0] = E;

    // Max heap for Dijkstra-style traversal: {energy, node}
    priority_queue<pair<double, int>> pq;
    pq.push({E, 0});

    while (!pq.empty()) {
        double cur_energy = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (cur_energy < max_energy[u]) continue; // Skip outdated entries

        for (int v : adj[u]) {
            double next_energy = cur_energy * scale[u];
            if (next_energy > max_energy[v]) {
                max_energy[v] = next_energy;
                pq.push({next_energy, v});
            }
        }
    }

    cout << fixed << setprecision(6) << max_energy[N - 1] << endl;
    return 0;
}
