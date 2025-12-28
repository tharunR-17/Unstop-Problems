#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> W(N);
    for (int i = 0; i < N; i++) {
        cin >> W[i];
    }

    const int OFFSET = 30000;
    const int MAXSUM = 60000;

    vector<vector<bool>> dp(N, vector<bool>(MAXSUM + 1, false));

    // Starting position
    dp[0][W[0] + OFFSET] = true;

    for (int i = 0; i < N; i++) {
        for (int s = 0; s <= MAXSUM; s++) {
            if (!dp[i][s]) continue;

            for (int jump = 1; jump <= K; jump++) {
                int j = i + jump;
                if (j >= N) break;

                int newSum = s + W[j];
                if (newSum >= 0 && newSum <= MAXSUM) {
                    dp[j][newSum] = true;
                }
            }
        }
    }

    if (dp[N - 1][OFFSET]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
