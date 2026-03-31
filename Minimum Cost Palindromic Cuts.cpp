#include <bits/stdc++.h>
using namespace std;

// Function to check if a substring is a palindrome
bool isPalindrome(const string &s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        ++start;
        --end;
    }
    return true;
}

int minPartitionCost(const string &s) {
    int n = s.size();

    // If the string is already a palindrome, cost is 0
    if (isPalindrome(s, 0, n - 1)) return 0;

    // DP array to store minimum cost for partitions
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    // Precomputing palindrome states for substrings
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) isPalin[i][i] = true; // Single chars are palindromes
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                isPalin[i][j] = (len == 2) ? true : isPalin[i + 1][j - 1];
            }
        }
    }

    // Compute minimum cost partitions
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (isPalin[j][i - 1]) {
                int cost = (j > 0) ? (s[j - 1] + s[i - 1]) : 0;
                dp[i] = min(dp[i], dp[j] + cost);
            }
        }
    }

    return dp[n];
}

int main() {
    string S;
    cin >> S;
    cout << minPartitionCost(S) << endl;
    return 0;
}
