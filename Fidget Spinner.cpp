#include <iostream>
#include <vector>
#define MOD 1000000007

using namespace std;

int ways(int N) {
    vector<int> dp(N + 1, 0);
    dp[0] = 1; // Base case

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i - j >= 0) {
                dp[i] = (dp[i] + dp[i - j]) % MOD;
            }
        }
    }
    return dp[N];
}

int main() {
    int n;
    cin >> n;
    cout << ways(n) << endl;
    return 0;
}
