#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    queue<pair<int, int>> q;

    int a, b;
    cin >> a >> b;

    vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));

    dp[a][0] = 1;
    q.push({a, 0});

    while (!q.empty()) {
        auto current = q.front(); q.pop();
        int parity = current.second;
        int node = current.first;

        for (const Edge& edge : graph[node]) {
            int nex = (parity + (edge.weight % 2 + 2) % 2) % 2;
            int next = edge.to;

            if (dp[next][nex] == 0) {
                q.push({next, nex});
            }
            dp[next][nex] = (dp[next][nex] + dp[node][parity]) % MOD;
        }
    }   
    cout << (dp[b][0] > 0 ? dp[b][0] : -1) << endl;
    return 0;
}
