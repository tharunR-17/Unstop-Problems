#include <iostream>
#include <unordered_map>
using namespace std;

const int MOD = 1e9 + 7;

int countDivisibleSubarrays(int arr[], int n, int k) {
    unordered_map<int, int> count;
    count[0] = 1;

    long long prefixSum = 0;
    int result = 0;

    for (int i = 0; i < n; ++i) {
        prefixSum += arr[i];
        int mod = ((prefixSum % k) + k) % k;  // Normalize mod for negatives

        result = (result + count[mod]) % MOD;
        count[mod]++;
    }

    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    int arr[n];

    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    cout << countDivisibleSubarrays(arr, n, k) << endl;
    return 0;
}
