#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<long long> H(N);
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }

    // dp[i][k] = max altitude gain ending at station i using k rides
    vector<vector<long long>> dp(N, vector<long long>(K + 1, 0));

    long long ans = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (H[j] < H[i]) {
                long long gain = H[i] - H[j];
                for (int k = 1; k <= K; k++) {
                    dp[i][k] = max(dp[i][k], dp[j][k - 1] + gain);
                }
            }
        }
        for (int k = 0; k <= K; k++) {
            ans = max(ans, dp[i][k]);
        }
    }

    cout << ans << "\n";
    return 0;
}
