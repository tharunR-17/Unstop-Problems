#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int findMinAttempts(int floors, int parachutes) {
    vector<vector<int>> dp(parachutes + 1, vector<int>(floors + 1, 0));
    
    for (int i = 1; i <= parachutes; ++i) {
        for (int j = 1; j <= floors; ++j) {
            dp[i][j] = j;
        }
    }
    
    for (int i = 2; i <= parachutes; ++i) {
        for (int j = 1; j <= floors; ++j) {
            for (int x = 1; x < j; ++x) {
                dp[i][j] = min(dp[i][j], 1 + max(dp[i - 1][x - 1], dp[i][j - x]));
            }
        }
    }
    
    return dp[parachutes][floors];
}

int main() {
    int N, K;
    cin >> N >> K;
    
    cout << findMinAttempts(N, K) << endl;
    
    return 0;
}
