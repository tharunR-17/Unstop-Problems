#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Placeholder function for user logic
int maxSumPath(int N, int L, vector<vector<int>>& grid) {
    if (N == 0) return 0;

    vector<long long> prev_dp(N);

    for (int j = 0; j < N; ++j) {
        prev_dp[j] = grid[0][j];
    }

    for (int i = 1; i < N; ++i) {
        vector<long long> current_dp(N);
        deque<int> window_max_indices; 

        int R_limit = 0; 

        for (int j = 0; j < N; ++j) {
            
            while (R_limit < N && R_limit <= j + L) {
                while (!window_max_indices.empty() && 
                       prev_dp[window_max_indices.back()] <= prev_dp[R_limit]) {
                    window_max_indices.pop_back();
                }
                window_max_indices.push_back(R_limit);
                R_limit++;
            }
            
            if (!window_max_indices.empty() && window_max_indices.front() < j - L) {
                window_max_indices.pop_front();
            }

            long long max_prev_sum = prev_dp[window_max_indices.front()];
            
            current_dp[j] = grid[i][j] + max_prev_sum;
        }

        prev_dp = current_dp;
    }

    long long max_sum = numeric_limits<long long>::min();
    for (int j = 0; j < N; ++j) {
        max_sum = max(max_sum, prev_dp[j]);
    }

    return (int)max_sum;
}

int main() {
    int N, L;
    cin >> N >> L;
    
    vector<vector<int>> grid(N, vector<int>(N));
    
    // Reading the grid values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    
    // Call the user logic function and print the output
    int result = maxSumPath(N, L, grid);
    cout << result << endl;

    return 0;
}
