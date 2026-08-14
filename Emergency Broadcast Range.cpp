#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    priority_queue<pair<long long, int>> pq;
    vector<long long> best(n, -1);

    for (int i = 0; i < k; ++i) {
        int t;
        long long p;
        cin >> t >> p;
        --t;

        if (p > best[t]) {
            best[t] = p;
            pq.push({p, t});
        }
    }

    int ans = 0;

    while (!pq.empty()) {
        auto [power, u] = pq.top();
        pq.pop();

        if (power != best[u])
            continue;

        ++ans;

        if (power == 0)
            continue;

        for (int v : g[u]) {
            long long np = power - 1;

            if (np > best[v]) {
                best[v] = np;
                pq.push({np, v});
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
