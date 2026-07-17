#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> p(n + 1);
    for (int i = 0; i <= n; i++) cin >> p[i];

    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j],
                               dp[i][k] + dp[k + 1][j] +
                               1LL * p[i] * p[k + 1] * p[j + 1]);
            }
        }
    }

    cout << dp[0][n - 1];
    return 0;
}
