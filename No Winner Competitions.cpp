#include <bits/stdc++.h>
using namespace std;

// N and MOD are constants used in the program
const int N = 505;
const int MOD = 1e9+7;

int n, m;
// c[i][j] stores the binomial coefficient "i choose j"
int c[N][N];
// dp[i][j] stores the number of ways to partition i items into j non-empty sets
int dp[N][N];

// add function returns (x + y) % MOD
int add(int x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
  return x;
}
// mul function returns (x * y) % MOD
int mul(int x, int y) {
  return x * 1ll * y % MOD;
}


int main() {
  // Read input
  cin >> n >> m;
  // Compute binomial coefficients using dynamic programming
  for (int i = 0; i <= n; ++i) {
    c[i][0] = c[i][i] = 1;
    for (int j = 1; j < i; ++j) 
      c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
  }
  // Initialize base case for dynamic programming
  dp[n][0] = 1;
  // Do dynamic programming
  for (int i = n; i > 1; i--) {
    for (int j = 0; j < m; ++j) {
      // Skip if there are no ways to partition i items into j non-empty sets
      if (!dp[i][j]) continue;
      // Initialize pw as 1
      int pw = 1;
      // nj is the maximum number of sets we can partition i items into given the current value of j
      int nj = min(m, j + i - 1);
      // Iterate over the number of sets k in the partition
      for (int k = i; k >= 0; k--) {
        // Update the number of ways to partition i items into nj sets
        dp[k][nj] = add(dp[k][nj], mul(dp[i][j], mul(c[i][k], pw)));
        // Update pw as pw * (nj - j)
        pw = mul(pw, nj - j);
      }
    }
  }
  // Initialize ans as 0
  int ans = 0;
  // Iterate over the number of sets in the partition
  for (int i = 0; i <= m; ++i)
    // Add the number of ways to partition 0 items into i sets to ans
    ans = add(ans, dp[0][i]);
  // Print the answer
  cout << ans << endl;
}
