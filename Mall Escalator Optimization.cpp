#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> adj(N);

    // Read escalators
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // directed edge
    }

    vector<int> dist(N, -1);  // -1 means unreachable
    queue<int> q;

    // Start BFS from floor 0
    dist[0] = 0;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {          // not visited
                dist[v] = dist[u] + 1;    // 1 minute per escalator
                q.push(v);
            }
        }
    }

    // Output results
    for (int i = 0; i < N; i++) {
        cout << dist[i] << " ";
    }

    return 0;
}
