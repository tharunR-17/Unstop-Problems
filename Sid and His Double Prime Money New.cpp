#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> prices(n);
    int max_price = 0;
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
        max_price = max(max_price, prices[i]);
    }

    // We need primes up to max_price + 2
    int L = max_price + 2;
    vector<bool> is_prime(L+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= L; p++) {
        if (!is_prime[p]) continue;
        for (int q = p * p; q <= L; q += p)
            is_prime[q] = false;
    }

    // Mark double primes: p is prime and p+2 is prime
    vector<bool> is_double(L+1, false);
    for (int p = 2; p + 2 <= L; p++) {
        if (is_prime[p] && is_prime[p+2]) {
            is_double[p] = true;
        }
    }

    int best_len = 0;
    long long best_sum = 0;

    // Track the current increasing segment
    int curr_len = 0;
    long long curr_sum = 0;
    int prev = -1;

    for (int x : prices) {
        if (curr_len == 0 || x > prev) {
            // continue the segment
            curr_len++;
            if (x <= L && is_double[x]) {
                curr_sum += x;
            }
        } else {
            // segment broke: compare against best
            if (curr_len > best_len ||
                (curr_len == best_len && curr_sum > best_sum)) {
                best_len = curr_len;
                best_sum = curr_sum;
            }
            // start new segment at x
            curr_len = 1;
            curr_sum = (x <= L && is_double[x] ? x : 0);
        }
        prev = x;
    }
    // final check
    if (curr_len > best_len ||
        (curr_len == best_len && curr_sum > best_sum)) {
        best_len = curr_len;
        best_sum = curr_sum;
    }

    cout << best_len << " " << best_sum << "\n";
    return 0;
}
