#include <iostream>
#include <vector>

// Function to check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false; // 1 is not prime
    if (n <= 3) return true;  // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Check divisors up to sqrt(n)
    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int main() {
    int M, N;
    if (!(std::cin >> M >> N)) return 0;

    std::vector<std::vector<int>> grid(M, std::vector<int>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> grid[i][j];
        }
    }

    std::vector<int> result;
    for (int i = 0; i < M; i++) {
        // Even row index (0, 2, 4...): Left to Right
        if (i % 2 == 0) {
            for (int j = 0; j < N; j++) {
                if (!isPrime(grid[i][j])) {
                    result.push_back(grid[i][j]);
                }
            }
        } 
        // Odd row index (1, 3, 5...): Right to Left
        else {
            for (int j = N - 1; j >= 0; j--) {
                if (!isPrime(grid[i][j])) {
                    result.push_back(grid[i][j]);
                }
            }
        }
    }

    // Final Output Logic
    if (result.empty()) {
        std::cout << -1 << std::endl;
    } else {
        for (int i = 0; i < result.size(); i++) {
            std::cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    return 0;
}
