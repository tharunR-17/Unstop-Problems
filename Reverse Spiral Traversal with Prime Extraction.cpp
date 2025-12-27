#include <iostream>
#include <vector>
#include <cmath>

// Prime check function
bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

// Spiral traversal starting from bottom-right
void reverse_spiral_and_primes(const std::vector<std::vector<int>>& matrix, int m, int n) {
    std::vector<int> spiral;
    std::vector<int> primes;

    int top = 0, bottom = m - 1;
    int left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        // ← bottom row
        for (int j = right; j >= left; j--)
            spiral.push_back(matrix[bottom][j]);
        bottom--;

        // ↑ left column
        for (int i = bottom; i >= top; i--)
            spiral.push_back(matrix[i][left]);
        left++;

        // → top row
        if (top <= bottom) {
            for (int j = left; j <= right; j++)
                spiral.push_back(matrix[top][j]);
            top++;
        }

        // ↓ right column
        if (left <= right) {
            for (int i = top; i <= bottom; i++)
                spiral.push_back(matrix[i][right]);
            right--;
        }
    }

    // Collect primes and compute their sum
    int prime_sum = 0;
    for (int val : spiral) {
        if (isPrime(val)) {
            primes.push_back(val);
            prime_sum += val;
        }
    }

    // First Output: Spiral traversal
    for (int val : spiral) std::cout << val << " ";
    std::cout << "\n";

    // Second Output: Primes or 0
    if (primes.empty()) {
        std::cout << "0\n";
    } else {
        for (int p : primes) std::cout << p << " ";
        std::cout << "\n";
    }

    // Third Output: Sum of primes
    std::cout << prime_sum << "\n";
}

int main() {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            std::cin >> matrix[i][j];

    reverse_spiral_and_primes(matrix, m, n);
    return 0;
}
