#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

// Function to generate all primes up to max_val using Sieve of Eratosthenes
vector<bool> generatePrimes(int max_val) {
    vector<bool> is_prime(max_val + 3, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= max_val + 2; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max_val + 2; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Read input
    int n;
    cin >> n;
    
    vector<int> prices(n);
    int max_price = 0;
    
    // Read prices and find maximum price
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
        max_price = max(max_price, prices[i]);
    }
    
    // Generate primes and identify double primes
    vector<bool> is_prime = generatePrimes(max_price + 2);
    unordered_set<int> double_primes;
    
    for (int i = 2; i <= max_price; ++i) {
        if (is_prime[i] && is_prime[i + 2]) {
            double_primes.insert(i);
        }
    }
    
    // Find longest strictly increasing subsequence and calculate sum
    int max_len = 1;
    int max_sum = double_primes.count(prices[0]) ? prices[0] : 0;
    int curr_len = 1;
    int curr_sum = max_sum;
    
    for (int i = 1; i < n; ++i) {
        if (prices[i] > prices[i - 1]) {
            // Continue the current subsequence
            curr_len++;
            if (double_primes.count(prices[i])) {
                curr_sum += prices[i];
            }
        } else {
            // Check if current subsequence is better
            if (curr_len > max_len || (curr_len == max_len && curr_sum > max_sum)) {
                max_len = curr_len;
                max_sum = curr_sum;
            }
            
            // Start a new subsequence
            curr_len = 1;
            curr_sum = double_primes.count(prices[i]) ? prices[i] : 0;
        }
    }
    
    // Final check for the last subsequence
    if (curr_len > max_len || (curr_len == max_len && curr_sum > max_sum)) {
        max_len = curr_len;
        max_sum = curr_sum;
    }
    
    // Output the result
    cout << max_len << " " << max_sum << endl;
    
    return 0;
}
