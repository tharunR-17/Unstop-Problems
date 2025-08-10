#include <bits/stdc++.h>
using namespace std;

int calculate_max_valid_squads(int N, int M, int K, vector<int>& specialization, vector<pair<int, int>>& connections) {
    // Placeholder logic function
    vector<vector<int>> adj(N);
    for (auto& conn : connections) {
        int u = conn.first;
        int v = conn.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> visited(N, false);
    int valid_squads = 0;

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            queue<int> q;
            unordered_set<int> specs;
            int size = 0;
            bool has_duplicate = false;

            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int curr = q.front(); q.pop();
                size++;
                if (specs.count(specialization[curr])) {
                    has_duplicate = true;
                }
                specs.insert(specialization[curr]);

                for (int neighbor : adj[curr]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            if (!has_duplicate && size >= K) {
                valid_squads++;
            }
        }
    }

    return valid_squads;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<int> specialization(N);
    for (int i = 0; i < N; ++i) {
        cin >> specialization[i];
    }

    vector<pair<int, int>> connections(M);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        connections[i] = make_pair(u - 1, v - 1); // Convert to 0-based index
    }

    int max_squads = calculate_max_valid_squads(N, M, K, specialization, connections);
    cout << max_squads << endl;

    return 0;
}
