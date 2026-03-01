#include <iostream>
using namespace std;

// Function to calculate modulo power
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to check if a number is a power of two
bool isPowerOfTwo(long long n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int main() {
    const int MOD = 10007;
    long long N;
    cin >> N;

    // Find modulo multiplicative inverse of N with respect to MOD
    long long inverse = power(N, MOD - 2, MOD);

    // Check if the inverse is a power of two and print the result
    cout << (isPowerOfTwo(inverse) ? 1 : 0) << endl;

    return 0;
}
