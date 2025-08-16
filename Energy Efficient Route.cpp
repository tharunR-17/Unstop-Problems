#include <bits/stdc++.h>
using namespace std;

// Placeholder function where user will implement the logic
int minEnergyCost(const std::vector<int>& energy, int N, int K) {
    // User should write their logic here
    // Parameters:
    // energy: vector of integers representing energy required at each checkpoint
    // N: number of checkpoints
    // K: maximum number of checkpoints that can be skipped
    // Return:
    // int: minimum total energy required to reach the last checkpoint from the first one

    vector<int>dp(N, INT_MAX);
    dp[0]=0;
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j <= K; ++j) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + abs(energy[i] - energy[i - j]));
            }
        }
    }

    return dp[N-1]; // Placeholder return value
}

int main() {
    int N, K;
    std::cin >> N >> K;
    
    std::vector<int> energy(N);
    for(int i = 0; i < N; ++i) {
        std::cin >> energy[i];
    }
    
    // Call the user logic function and print the output
    int result = minEnergyCost(energy, N, K);
    std::cout << result << std::endl;

    return 0;
}
