#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
bool isPrime(int x) {
    if (x < 2) return false;
    for (int i = 2; i*i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

int n;
vector<int> b;
vector<vector<int>> dp;

int dfs(int l, int r) {
    if (l + 1 == r) return 0; // no performer between l and r
    if (dp[l][r] != -1) return dp[l][r];
    
    int ans = 0;
    for (int i = l + 1; i < r; i++) {
        int score = (b[l]+2) * b[i] * (b[r]+2);
        if (isPrime(b[i])) score += b[i];
        ans = max(ans, dfs(l, i) + dfs(i, r) + score);
    }
    return dp[l][r] = ans;
}
int talentBurst(const std::vector<int>& arr) {
     n = arr.size();
    b = vector<int>(n + 2, 1);
    for (int i = 0; i < n; i++) b[i+1] = arr[i];
    
    dp.assign(n + 2, vector<int>(n + 2, -1));
    return dfs(0, n+1);
    return 0;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    // Call user logic function and print the output
    int result = talentBurst(arr);
    std::cout << result << std::endl;

    return 0;
}
