#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int N, K;
vector<ll> gold;
vector<vector<int>> adj;

ll X;                 // candidate minimum region sum
int regions;          // count of valid regions formed

ll dfs(int u, int parent) {
    ll sum = gold[u];

    for (int v : adj[u]) {
        if (v == parent) continue;
        sum += dfs(v, u);
    }

    // If this subtree can form a region
    if (sum >= X) {
        regions++;
        return 0;     // cut here → detach component
    }

    return sum;
}

bool can(ll mid) {
    X = mid;
    regions = 0;
    dfs(0, -1);

    // Need at least K+1 regions
    return regions >= K + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    gold.resize(N);
    adj.assign(N, {});

    for (int i = 0; i < N; i++) cin >> gold[i];

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll low = 0, high = 0;
    for (ll g : gold) high += g;

    ll ans = 0;

    while (low <= high) {
        ll mid = (low + high) / 2;

        if (can(mid)) {
            ans = mid;
            low = mid + 1;   // try bigger minimum
        } else {
            high = mid - 1;
        }
    }

    cout << ans << "\n";
    return 0;
}
