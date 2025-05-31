#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long long maxWeightedScore(const string& S, const vector<int>& weights) {
    int N = S.size();
    vector<vector<bool>> isPalindrome(N, vector<bool>(N, false));

    // Precompute isPalindrome[i][j]
    for (int len = 1; len <= N; ++len) {
        for (int i = 0; i <= N - len; ++i) {
            int j = i + len - 1;
            if (S[i] == S[j]) {
                if (len <= 2) {
                    isPalindrome[i][j] = true;
                } else {
                    isPalindrome[i][j] = isPalindrome[i + 1][j - 1];
                }
            }
        }
    }

    // Precompute prefix sum of character weights
    vector<long long> prefixWeight(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        prefixWeight[i + 1] = prefixWeight[i] + weights[S[i] - 'a'];
    }

    // DP computation
    vector<long long> dp(N, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (isPalindrome[j][i]) {
                long long weightSum = prefixWeight[i + 1] - prefixWeight[j];
                long long score = (i - j + 1) * weightSum;
                dp[i] = max(dp[i], (j > 0 ? dp[j - 1] : 0) + score);
            }
        }
    }

    return dp[N - 1];
}

int main() {
    int n;
    cin >> n;

    string S;
    cin >> S;

    vector<int> weights(26);
    for (int i = 0; i < 26; ++i) {
        cin >> weights[i];
    }

    long long result = maxWeightedScore(S, weights);
    cout << result << endl;

    return 0;
}
