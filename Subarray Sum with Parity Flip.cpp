#include <iostream>
#include <vector>
#include <unordered_map>

int count_parity_flipped_subarrays(int n, long long k, const std::vector<int>& arr) {
    std::unordered_map<long long, int> prefix_count;
    prefix_count[0] = 1;  // Base case: sum 0 occurs once
    
    long long current_sum = 0;
    int count = 0;
    
    for (int i = 0; i < n; ++i) {
        int transformed = (arr[i] % 2 == 0) ? arr[i] + 1 : arr[i] - 1;
        current_sum += transformed;

        // Check if current_sum - k was seen before
        if (prefix_count.find(current_sum - k) != prefix_count.end()) {
            count += prefix_count[current_sum - k];
        }

        // Add current_sum to the map
        prefix_count[current_sum]++;
    }

    return count;
}

int main() {
    int n;
    long long k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int result = count_parity_flipped_subarrays(n, k, arr);
    std::cout << result << std::endl;
    return 0;
}
