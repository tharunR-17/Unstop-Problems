#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<long long> freq(k, 0);

    freq[0] = 1;

    long long sum = 0;
    long long count = 0;

    for (int i = 0; i < n; i++) {

        sum += nums[i];

        int rem = sum % k;

        // For negative numbers, if allowed
        if (rem < 0) {
            rem += k;
        }

        count += freq[rem];

        freq[rem]++;
    }

    cout << count << endl;

    return 0;
}
