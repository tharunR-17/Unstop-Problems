#include <iostream>
#include <cmath>

const long long MOD = 1000000007;

bool is_prime(int x) {
    if (x <= 1) return false;
    for (int i = 2; i <= std::sqrt(x); i++) {
        if (x % i == 0) return false;
    }
    return true;
}

long long factorial(int x) {
    long long res = 1;
    for (int i = 2; i <= x; i++) res = (res * i) % MOD;
    return res;
}

long long numPrimeArrangements(int n) {
    int primes_count = 0;
    for (int i = 1; i <= n; i++) {
        if (is_prime(i)) primes_count++;
    }
    return (factorial(primes_count) * factorial(n - primes_count)) % MOD;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << numPrimeArrangements(n) << std::endl;
    return 0;
}
