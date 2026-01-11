#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> weights(n);
    for(int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    int k;
    cin >> k;

    if (k > n) {
        cout << -1 << "\n";
        return 0;
    }

    const int INF = 1e9;
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            int max_w = 0;
            for (int p = i - 1; p >= 0; p--) {
                max_w = max(max_w, weights[p]);
                dp[i][j] = min(dp[i][j], dp[p][j - 1] + max_w);
            }
        }
    }

    int ans = dp[n][k];
    cout << (ans >= INF ? -1 : ans) << "\n";

    return 0;
}
