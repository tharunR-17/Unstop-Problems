#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, maxBooks, k;
    cin >> n >> maxBooks >> k;

    vector<int> books(n);
    for(int i = 0; i < n; i++)
        cin >> books[i];

    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, INF));
    dp[0][0] = 0;

    for(int i = 0; i < n; i++) {
        for(int r = 0; r <= k; r++) {
            if(dp[i][r] == INF) continue;

            // Option 1: remove this book
            if(r + 1 <= k)
                dp[i + 1][r + 1] = min(dp[i + 1][r + 1], dp[i][r]);

            // Option 2: form a box starting at i
            multiset<int> chosen;   // smallest maxBooks elements
            long long removed = 0;

            for(int j = i; j < n; j++) {
                chosen.insert(books[j]);

                if((int)chosen.size() > maxBooks) {
                    // remove the largest (so we keep smallest maxBooks)
                    auto it = prev(chosen.end());
                    chosen.erase(it);
                    removed++;
                }

                if(r + removed > k) break;

                if(!chosen.empty()) {
                    long long cost = *prev(chosen.end());
                    dp[j + 1][r + removed] = min(
                        dp[j + 1][r + removed],
                        dp[i][r] + cost
                    );
                }
            }
        }
    }

    long long ans = INF;
    for(int r = 0; r <= k; r++)
        ans = min(ans, dp[n][r]);

    cout << ans << "\n";
    return 0;
}
