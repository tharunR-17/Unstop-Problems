#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    const long long INF = 4e18;

    vector<vector<long long>> dist(N + 1, vector<long long>(N + 1, INF));

    for (int i = 1; i <= N; i++)
        dist[i][i] = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= N; j++) {
                if (dist[k][j] == INF) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    while (Q--) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] == INF)
            cout << -1 << '\n';
        else
            cout << dist[a][b] << '\n';
    }

    return 0;
}
