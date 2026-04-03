#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<vector<int>> grid(N, vector<int>(N));
    vector<vector<int>> dp(N, vector<int>(N, INT_MAX));

    // Input the grid
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }

    // Initialize the first row of dp with the grid's first row
    for (int j = 0; j < N; ++j) {
        dp[0][j] = grid[0][j];
    }

    // Fill the DP table
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                if (j != k) { // Avoid selecting the same column
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + grid[i][j]);
                }
            }
        }
    }

    // Find the minimum value in the last row
    int result = INT_MAX;
    for (int j = 0; j < N; ++j) {
        result = min(result, dp[N - 1][j]);
    }

    cout << result << endl;

    return 0;
}
