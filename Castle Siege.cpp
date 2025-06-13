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

#include <bits/stdc++.h>
using namespace std;

int compute_min_siege(int rows,
                      int cols,
                      vector<vector<int>>& defense,
                      int limit) 
{
    static const int UNREACHABLE = 1e9;
    // siege_dp[r][c] = minimal possible “max defense” on any (0,0)->(r,c) path
    vector<vector<int>> siege_dp(rows, vector<int>(cols, UNREACHABLE));
    siege_dp[0][0] = defense[0][0];

    // initialize top row (only from left)
    for (int c = 1; c < cols; ++c) {
        siege_dp[0][c] = max(siege_dp[0][c-1], defense[0][c]);
    }
    // initialize left column (only from above)
    for (int r = 1; r < rows; ++r) {
        siege_dp[r][0] = max(siege_dp[r-1][0], defense[r][0]);
    }

    // fill the rest
    for (int r = 1; r < rows; ++r) {
        for (int c = 1; c < cols; ++c) {
            int viaAbove = max(siege_dp[r-1][c], defense[r][c]);
            int viaLeft  = max(siege_dp[r][c-1], defense[r][c]);
            siege_dp[r][c] = min(viaAbove, viaLeft);
        }
    }

    int result = siege_dp[rows-1][cols-1];
    return (result <= limit ? result : -1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols, limit;
    cin >> rows >> cols;

    vector<vector<int>> defense(rows, vector<int>(cols));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            cin >> defense[r][c];
        }
    }
    cin >> limit;

    cout << compute_min_siege(rows, cols, defense, limit) << "\n";
    return 0;
}
