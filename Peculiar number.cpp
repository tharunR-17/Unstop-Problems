#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// Function to calculate Fibonacci numbers
int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

// Function to check if we can partition the array into k parts with max sum <= maxSum
bool canPartition(const vector<int>& arr, int k, int maxSum) {
    int currentSum = 0;
    int partitions = 1; // Start with one partition

    for (int num : arr) {
        if (currentSum + num > maxSum) {
            // Start a new partition
            partitions++;
            currentSum = num; // Start new partition with current number
            if (partitions > k) return false; // More partitions than allowed
        } else {
            currentSum += num; // Add to current partition
        }
    }
    return true; // We can partition within the limit
}

// Function to find the peculiar number
int peculiarNumber(int n, int k, vector<int>& arr) {
    // Step 1: Transform the array
    for (int i = 0; i < n; ++i) {
        arr[i] = abs(arr[i] - i);
    }

    // Step 2: Binary search for the minimum possible maximum sum
    int left = *max_element(arr.begin(), arr.end());
    int right = accumulate(arr.begin(), arr.end(), 0);
    int result = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canPartition(arr, k, mid)) {
            result = mid; // Found a valid partitioning
            right = mid - 1; // Try for a smaller max sum
        } else {
            left = mid + 1; // Increase the max sum
        }
    }

    // Step 3: Determine the peculiar number
    if (result < 100) {
        return fibonacci(result);
    } else {
        return result;
    }
}
int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> arr(n);
    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Call user logic function and print the output
    int result = peculiarNumber(n, k, arr);
    cout << result << endl;

    return 0;
}
