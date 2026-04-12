#include <iostream>
#include <vector>

using namespace std;

// Function where the user will implement their logic
int helper(int N, int B, const vector<int>& entryFees, const vector<int>& happiness, vector<vector<int>>& dp){
    if (N <= 0 || B <= 0) {
        return 0;
    }

    if (dp[N][B] != -1) {
        return dp[N][B];
    }

    int leave = helper(N - 1, B, entryFees, happiness, dp);

    int take = 0;
    if (entryFees[N - 1] <= B) {
        take = happiness[N - 1] + helper(N - 2, B - entryFees[N - 1], entryFees, happiness, dp);
    }
    return dp[N][B] = max(take, leave);
}

int calculateMaxHappiness(int N, int B, const vector<int>& entryFees, const vector<int>& happiness) {
    // User logic to be implemented here
    vector<vector<int>> dp(N + 1, vector<int>(B + 1, -1));
    return helper(N, B, entryFees, happiness, dp);// Placeholder return
}

int main() {
    int N, B;
    cin >> N >> B;

    vector<int> entryFees(N);
    vector<int> happiness(N);

    for (int i = 0; i < N; ++i) {
        cin >> entryFees[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> happiness[i];
    }

    // Call the user logic function and print the result
    int result = calculateMaxHappiness(N, B, entryFees, happiness);
    cout << result << endl;

    return 0;
}
