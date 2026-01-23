#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int N;
vector<vector<pair<int,int>>> adj;
vector<long long> D;
long long answer = 0;

void dfs(int u, int parent, int lastW, long long &sum) {
    sum += D[u];

    for (auto &[v, w] : adj[u]) {
        if (v == parent) continue;
        if (w > lastW) {
            dfs(v, u, w, sum);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    adj.resize(N);
    D.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for (int i = 0; i < N; i++) {
        cin >> D[i];
    }

    for (int hub = 0; hub < N; hub++) {
        long long sum = 0;
        dfs(hub, -1, -1, sum); // lastW = -1 allows all first edges
        answer = max(answer, sum);
    }

    cout << answer << "\n";
    return 0;
}
