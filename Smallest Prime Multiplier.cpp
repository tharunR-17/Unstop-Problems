#include <iostream>

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

long long compute_x(long long p, long long n) {
    // Calculate LCM using the formula
    long long lcm = (p * n) / gcd(p, n);
    return lcm;
}

int main() {
    long long p, n;
    std::cin >> p >> n;
    
    // Call user logic function and print the output
    long long result = compute_x(p, n);
    std::cout << result << std::endl;
    
    return 0;
}
