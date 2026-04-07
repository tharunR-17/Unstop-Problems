#include <iostream>
#include <vector>
#include <numeric>

std::string decide_division(int n, const std::vector<int>& bundles) {
    int total_sum = 0;
    for (int x : bundles) {
        total_sum += x;
    }

    // If the total sum is odd, we can't split it equally
    if (total_sum % 2 != 0) {
        return "phoenix";
    }

    int target = total_sum / 2;
    // dp[i] will be true if a sum of i is possible
    std::vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int weight : bundles) {
        // Iterate backwards to ensure each bundle is used only once
        for (int j = target; j >= weight; --j) {
            if (dp[j - weight]) {
                dp[j] = true;
            }
        }
    }

    return dp[target] ? "partners" : "phoenix";
}

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    std::vector<int> bundles(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> bundles[i];
    }
    
    std::string result = decide_division(n, bundles);
    std::cout << result << std::endl;
    
    return 0;
}
