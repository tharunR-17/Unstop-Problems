#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> energy(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> energy[i];
    }

    // dp[i] stores the minimum cost to reach index i
    vector<long long> dp(n + 1, LLONG_MAX);
    dp[1] = 0;

    for (int j = 2; j <= n; j++) {
        for (int i = 1; i < j; i++) {
            if (dp[i] == LLONG_MAX) continue;
            
            long long cost = dp[i] + llabs(energy[i] - energy[j]) * (j - i);
            dp[j] = min(dp[j], cost);
        }
    }

    cout << dp[n] << "\n";
    return 0;
}
