#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function where user will write their logic
long minBalancingCost(const vector<vector<int>>& matrix, int N, int M) {
    long long totalCost = 0;

    for (int i = 0; i < N; ++i) {
        const vector<int>& row = matrix[i];
        long long sum = 0;
        for (int val : row) sum += val;

        int target = sum / M;

        vector<long long> imbalance(M);
        for (int j = 0; j < M; ++j) {
            imbalance[j] = row[j] - target;
        }

        vector<long long> prefix(M);
        prefix[0] = imbalance[0];
        for (int j = 1; j < M; ++j) {
            prefix[j] = prefix[j - 1] + imbalance[j];
        }

        sort(prefix.begin(), prefix.end());
        long long median = prefix[M / 2];

        long long cost = 0;
        for (long long p : prefix) {
            cost += abs(p - median);
        }

        totalCost += cost;
    }

    return totalCost;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<int>> matrix(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i][j];
        }
    }
    
    long result = minBalancingCost(matrix, N, M);
    cout << result << endl;

    return 0;
}
