#include <iostream>
using namespace std;

int calculateX(int N) {
    // Base cases
    if (N == 0) return 5;
    if (N == 1) return 3;

    // Initialize variables for F(N-2) and F(N-1)
    int prev2 = 5; // F(0)
    int prev1 = 3; // F(1)
    int current = 0;

    // Calculate F(N) iteratively
    for (int i = 2; i <= N; i++) {
        if (i % 2 == 0) {
            current = (prev1 * prev2) % 999; // Even case
        } else {
            current = (prev1 + prev2) % 998; // Odd case
        }
        // Update prev2 and prev1 for the next iteration
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main() {
    int N;
    cin >> N; // Input
    cout << calculateX(N) << endl; // Output
    return 0;
}
