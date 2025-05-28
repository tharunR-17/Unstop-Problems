#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m, X;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    vector<vector<int>> dp(n, vector<int>(m, INT_MAX));

    // Input grid
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];

    cin >> X;

    // Base case
    dp[0][0] = grid[0][0];

    // DP calculation
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dp[i][j] == INT_MAX) continue;

            // Move right
            if (j + 1 < m) {
                int newPower = max(dp[i][j], grid[i][j + 1]);
                if (newPower <= X)
                    dp[i][j + 1] = min(dp[i][j + 1], newPower);
            }

            // Move down
            if (i + 1 < n) {
                int newPower = max(dp[i][j], grid[i + 1][j]);
                if (newPower <= X)
                    dp[i + 1][j] = min(dp[i + 1][j], newPower);
            }
        }
    }

    // Output
    if (dp[n - 1][m - 1] == INT_MAX)
        cout << -1 << endl;
    else
        cout << dp[n - 1][m - 1] << endl;

    return 0;
}
