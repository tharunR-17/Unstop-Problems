#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

pair<int, int> findMinCostAndMax(const vector<vector<int>>& grid, int N, int M, int K) {
    int minTotal = numeric_limits<int>::max();
    int minMax = numeric_limits<int>::max();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= M - K; ++j) {
            int sum = 0;
            int currMax = 0;
            for (int x = 0; x < K; ++x) {
                sum += grid[i][j + x];
                currMax = max(currMax, grid[i][j + x]);
            }
            if (sum < minTotal || (sum == minTotal && currMax < minMax)) {
                minTotal = sum;
                minMax = currMax;
            }
        }
    }

    for (int j = 0; j < M; ++j) {
        for (int i = 0; i <= N - K; ++i) {
            int sum = 0;
            int currMax = 0;
            for (int x = 0; x < K; ++x) {
                sum += grid[i + x][j];
                currMax = max(currMax, grid[i + x][j]);
            }
            if (sum < minTotal || (sum == minTotal && currMax < minMax)) {
                minTotal = sum;
                minMax = currMax;
            }
        }
    }

    return make_pair(minTotal, minMax);
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> grid[i][j];

    pair<int, int> result = findMinCostAndMax(grid, N, M, K);
    cout << result.first << " " << result.second << endl;

    return 0;
}
