#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    // Extract digits
    vector<int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }

    // Sort digits for permutation
    sort(digits.begin(), digits.end());

    int ans = INT_MAX;

    // Try all permutations
    do {
        int A = digits[0] * 10 + digits[1];
        int B = digits[2] * 10 + digits[3];

        ans = min(ans, A * B);

    } while (next_permutation(digits.begin(), digits.end()));

    cout << ans << endl;

    return 0;
}
