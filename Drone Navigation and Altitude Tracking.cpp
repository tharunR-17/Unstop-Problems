#include <iostream>
#include <vector>
#include <climits>
using namespace std;

long long findMaxSubarraySum(vector<int>& arr, int n) {
    long long maxSum = INT_MIN, currentSum = 0;
    for (int i = 0; i < n; i++) {
        currentSum += arr[i];
        if (currentSum < 0) {
            currentSum = 0;
        }
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << findMaxSubarraySum(arr, n);
    return 0;
}
