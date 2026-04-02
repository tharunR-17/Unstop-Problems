#include <iostream>
#include <unordered_map>
using namespace std;

// Memoization table
unordered_map<int, long long> memo;

// Function to calculate the maximum enhancement level
long long maximizeEnhancement(int n) {
    // Base case: if n is less than or equal to 1, return n
    if (n <= 1) return n;

    // Check if the result is already computed
    if (memo.count(n)) return memo[n];

    // Compute the maximum enhancement by considering all possibilities
    long long keepAsIs = n;
    long long splitAndEnhance = maximizeEnhancement(n / 2) + maximizeEnhancement(n / 3) + maximizeEnhancement(n / 4);

    // Store the result in the memoization table
    memo[n] = max(keepAsIs, splitAndEnhance);

    return memo[n];
}

int main() {
    int n;
    cin >> n;  // Input the initial genetic alteration value

    cout << maximizeEnhancement(n) << endl;  // Output the maximum enhancement level

    return 0;
}
