#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> h(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
    }

    const long long INF = LLONG_MAX / 4;
    vector<long long> dp(N + 1, INF);

    dp[1] = 0;

    for (int i = 2; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            long long cost = llabs(h[i] - h[j]) * (i - j);
            dp[i] = min(dp[i], dp[j] + cost);
        }
    }

    cout << dp[N] << "\n";
    return 0;
}
