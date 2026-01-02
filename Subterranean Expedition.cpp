#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    // Read the values (artifacts or traps) at each cave
    vector<int> caveValues(N);
    for (int i = 0; i < N; ++i) {
        cin >> caveValues[i];
    }

    // Create adjacency list for the graph
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // DP array to store maximum artifacts value at each cave with 'step' moves
    vector<vector<int>> dp(N, vector<int>(K + 1, INT_MIN));
    dp[0][0] = caveValues[0];

    // BFS queue: pair of (cave index, step count)
    queue<pair<int, int>> q;
    q.push({0, 0});

    while (!q.empty()) {
        int u = q.front().first;
        int steps = q.front().second;
        q.pop();

        if (steps >= K) continue;

        for (int v : adj[u]) {
            int newSteps = steps + 1;
            int newValue = dp[u][steps] + caveValues[v];

            if (newValue > dp[v][newSteps]) {
                dp[v][newSteps] = newValue;
                q.push({v, newSteps});
            }
        }
    }

    // Find maximum artifact value at cave N-1 with any steps <= K
    int maxArtifacts = INT_MIN;
    for (int i = 0; i <= K; ++i) {
        maxArtifacts = max(maxArtifacts, dp[N - 1][i]);
    }

    if (maxArtifacts == INT_MIN) {
        cout << -1 << endl;
    } else {
        cout << maxArtifacts << endl;
    }

    return 0;
}
