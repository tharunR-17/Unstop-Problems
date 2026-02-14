#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> price(n), nutrition(n);
    for (int i = 0; i < n; i++) cin >> price[i];
    for (int i = 0; i < n; i++) cin >> nutrition[i];

    // dp[money][coupons_used]
    vector<vector<int>> dp(m + 1, vector<int>(k + 1, 0));

    for (int i = 0; i < n; i++) {
        int full = price[i];
        int half = price[i] / 2;

        for (int money = m; money >= 0; money--) {
            for (int c = k; c >= 0; c--) {

                // Buy at full price
                if (money >= full) {
                    dp[money][c] = max(dp[money][c],
                                       dp[money - full][c] + nutrition[i]);
                }

                // Buy with coupon
                if (c > 0 && money >= half) {
                    dp[money][c] = max(dp[money][c],
                                       dp[money - half][c - 1] + nutrition[i]);
                }
            }
        }
    }

    int ans = 0;
    for (int money = 0; money <= m; money++)
        for (int c = 0; c <= k; c++)
            ans = max(ans, dp[money][c]);

    cout << ans << endl;
    return 0;
}
       
