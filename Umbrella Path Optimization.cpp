#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minWetCells(int N, int M, vector<vector<int>>& grid) {
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(N, vector<int>(M, 1e9)));

    if (grid[0][0] == 0) {
        dp[0][0][0] = 0;
    } else if (grid[0][0] == 1) {
        dp[0][0][0] = 1;
    } else if (grid[0][0] == 2) {
        dp[0][0][0] = 0;
        dp[1][0][0] = 0;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == 0 && j == 0) continue;

            int prev0 = 1e9;
            int prev1 = 1e9;

            if (i > 0) {
                prev0 = min(prev0, dp[0][i - 1][j]);
                prev1 = min(prev1, dp[1][i - 1][j]);
            }
            if (j > 0) {
                prev0 = min(prev0, dp[0][i][j - 1]);
                prev1 = min(prev1, dp[1][i][j - 1]);
            }

            if (grid[i][j] == 0) {
                dp[0][i][j] = prev0;
                dp[1][i][j] = prev1;
            } else if (grid[i][j] == 1) {
                if (prev0 != 1e9) dp[0][i][j] = prev0 + 1;
                if (prev1 != 1e9) dp[1][i][j] = prev1;
            } else if (grid[i][j] == 2) {
                dp[0][i][j] = prev0;
                dp[1][i][j] = min(prev0, prev1);
            }
        }
    }

    int ans = min(dp[0][N - 1][M - 1], dp[1][N - 1][M - 1]);
    return (ans >= 1e9) ? -1 : ans;
}

int main() {
    int N, M;
    if (cin >> N >> M) {
        vector<vector<int>> grid(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> grid[i][j];
            }
        }
        cout << minWetCells(N, M, grid) << "\n";
    }

    return 0;
}
