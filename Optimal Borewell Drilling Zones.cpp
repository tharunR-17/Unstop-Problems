#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int N, M;
vector<vector<int>> grid;

// Generate all valid row masks (no adjacent 1s)
vector<int> getValidMasks(int m) {
    vector<int> masks;
    for (int mask = 0; mask < (1 << m); ++mask) {
        if ((mask & (mask << 1)) == 0)
            masks.push_back(mask);
    }
    return masks;
}

// Get sum of grid[row][col] where bit is set in mask
int getRowSum(const vector<int>& row, int mask) {
    int sum = 0;
    for (int i = 0; i < M; ++i) {
        if ((mask >> i) & 1)
            sum += row[i];
    }
    return sum;
}

int main() {
    cin >> N >> M;
    grid.assign(N, vector<int>(M));
    
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> grid[i][j];

    vector<int> validMasks = getValidMasks(M);
    vector<unordered_map<int, int>> dp(N);

    for (int mask : validMasks)
        dp[0][mask] = getRowSum(grid[0], mask);

    for (int row = 1; row < N; ++row) {
        for (int currMask : validMasks) {
            int currSum = getRowSum(grid[row], currMask);
            for (const auto& prev : dp[row - 1]) {
                int prevMask = prev.first;
                if ((currMask & prevMask) == 0) {
                    int total = prev.second + currSum;
                    dp[row][currMask] = max(dp[row][currMask], total);
                }
            }
        }
    }

    int result = 0;
    for (const auto& val : dp[N - 1])
        result = max(result, val.second);

    cout << result << endl;
    return 0;
}
