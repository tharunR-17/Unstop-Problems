#include <iostream>
#include <vector>
#include <set>
#include <cmath>

void user_logic(int n, std::vector<int>& nums);

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }
    
    user_logic(n, nums);
    
    return 0;
}

void user_logic(int n, std::vector<int>& nums) {
    // Write your logic here.
    std::set<int> unique(nums.begin(), nums.end());
    long long sum = 0;
    for (int val : unique) {
        sum += (1LL << val);
    }
    std::cout << sum << std::endl;
}
