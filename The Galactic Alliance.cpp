#include <bits/stdc++.h>
using namespace std;

static const long long NEG_INF = -1e18;

int N, K;
vector<long long> energy;
vector<vector<int>> tree;
vector<vector<vector<long long>>> dp;
vector<int> subSize;

void dfs(int u, int parent) {
    dp[u].assign(2, vector<long long>(K + 1, NEG_INF));
    dp[u][0][0] = 0;
    dp[u][1][1] = energy[u];
    subSize[u] = 1;

    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs(v, u);

        vector<long long> new0(K + 1, NEG_INF);
        vector<long long> new1(K + 1, NEG_INF);

        for (int i = 0; i <= min(subSize[u], K); i++) {
            if (dp[u][0][i] > NEG_INF) {
                for (int j = 0; j <= min(subSize[v], K - i); j++) {
                    long long best = max(dp[v][0][j], dp[v][1][j]);
                    if (best > NEG_INF)
                        new0[i + j] = max(new0[i + j], dp[u][0][i] + best);
                }
            }

            if (dp[u][1][i] > NEG_INF) {
                for (int j = 0; j <= min(subSize[v], K - i); j++) {
                    if (dp[v][0][j] > NEG_INF)
                        new1[i + j] = max(new1[i + j], dp[u][1][i] + dp[v][0][j]);
                }
            }
        }

        dp[u][0] = new0;
        dp[u][1] = new1;
        subSize[u] += subSize[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    energy.resize(N);
    for (int i = 0; i < N; i++) cin >> energy[i];

    tree.assign(N, {});
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dp.resize(N);
    subSize.resize(N);

    dfs(0, -1);

    long long ans = max(dp[0][0][K], dp[0][1][K]);

    if (ans == NEG_INF) cout << -1 << "\n";
    else cout << ans << "\n";

    return 0;
}
