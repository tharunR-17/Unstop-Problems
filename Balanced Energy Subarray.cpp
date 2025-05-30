#include <iostream>
#include <vector>

int count_balanced_subarrays(const std::vector<int>& arr, int k) {
    int n = arr.size();
    std::vector<int> prefix(n + 1, 0);

    // Build prefix sum array
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + arr[i];
    }

    int count = 0;

    for (int i = 0; i <= n - k; ++i) {
        int left_sum, right_sum;
        if (k % 2 == 0) {
            int half = k / 2;
            left_sum = prefix[i + half] - prefix[i];
            right_sum = prefix[i + k] - prefix[i + half];
        } else {
            int half = k / 2;
            left_sum = prefix[i + half] - prefix[i];
            right_sum = prefix[i + k] - prefix[i + half + 1];
        }

        if (left_sum == right_sum) {
            ++count;
        }
    }

    return count;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int result = count_balanced_subarrays(arr, k);
    std::cout << result << std::endl;
    return 0;
}
