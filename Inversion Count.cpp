#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    
    // Reading the array elements
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    int count = 0; // To store the count of valid pairs
    
    // Brute-force approach to check every pair (i, j) where i < j
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Calculate XOR and AND for the pair
            int xor_val = A[i] ^ A[j];
            int and_val = A[i] & A[j];
            
            // Check the condition
            if (xor_val <= and_val) {
                count++;
            }
        }
    }
    
    // Output the result
    cout << count << endl;
    
    return 0;
}
