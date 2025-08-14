#include <bits/stdc++.h>
using namespace std;

// Placeholder for user logic
int maxProfit(const vector<int>& profits) {
    // Write your logic here
    // Parameters:
    //     profits (vector<int>): List of integers representing profits
    // Returns:
    //     int: Maximum profit that can be earned
    int n = profits.size();

    if (n == 0) return 0;
    if (n == 1) return profits[0];

    vector<int> dp(n);

    dp[0] = profits[0];
    dp[1] = max(profits[0], profits[1]);

    for (int i = 2; i < n; ++i) {
        dp[i] = max(dp[i - 1], dp[i - 2] + profits[i]);
    }

    return dp[n - 1];
}

int main() {
    int N;
    cin >> N;
    vector<int> profits(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> profits[i];
    }
    
    // Call user logic function and print the output
    int result = maxProfit(profits);
    cout << result << endl;
    
    return 0;
}
