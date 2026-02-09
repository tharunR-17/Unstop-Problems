#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<long long> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // Step 1: Sort the array
    sort(arr.begin(), arr.end());

    // Step 2: Flip negative numbers while we have operations
    for (int i = 0; i < N && K > 0; i++) {
        if (arr[i] < 0) {
            arr[i] = -arr[i];
            K--;
        } else {
            break;
        }
    }

    // Step 3: Compute the sum and minimum absolute value
    long long sum = 0;
    long long minAbs = LLONG_MAX;

    for (long long x : arr) {
        sum += x;
        minAbs = min(minAbs, llabs(x));
    }

    // Step 4: If K is odd, flip the smallest absolute value once
    if (K % 2 == 1) {
        sum -= 2 * minAbs;
    }

    // Step 5: Output result
    cout << sum << "\n";

    return 0;
}
