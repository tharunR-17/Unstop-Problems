#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<pair<int,int>>> g(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<ll> dist(N + 1), mx(N + 1), mn(N + 1), ans(N + 1);

    function<void(int,int)> dfs = [&](int u, int p) {
        mx[u] = mn[u] = dist[u];
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            dist[v] = dist[u] + w;
            dfs(v, u);
            mx[u] = max(mx[u], mx[v]);
            mn[u] = min(mn[u], mn[v]);
        }
        ans[u] = mx[u] - mn[u];
    };

    dfs(1, 0);

    int Q;
    cin >> Q;
    while (Q--) {
        int v;
        cin >> v;
        cout << ans[v] << '\n';
    }

    return 0;
}
