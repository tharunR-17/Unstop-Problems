#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int longestBalancedSubarray(vector<int>& arr) {
    int n = arr.size();
    int maxLength = 1;
    
    // Try all possible starting positions
    for (int i = 0; i < n; i++) {
        unordered_map<int, int> freq;
        
        for (int j = i; j < n; j++) {
            freq[arr[j]]++;
            
            int subarrayLength = j - i + 1;
            int distinctCount = freq.size();
            
            // Quick check: length must be divisible by distinct count
            if (subarrayLength % distinctCount != 0) {
                continue;
            }
            
            int expectedFreq = subarrayLength / distinctCount;
            
            // Check if all frequencies match expectedFreq
            bool isBalanced = true;
            int actualSum = 0;
            
            for (const auto& pair : freq) {
                if (pair.second != expectedFreq) {
                    isBalanced = false;
                    break;
                }
                actualSum += pair.second;
            }
            
            // Double check: sum should equal subarray length
            if (isBalanced && actualSum == subarrayLength) {
                maxLength = max(maxLength, subarrayLength);
            }
            
            // Pruning: if any frequency is already too high, break
            bool shouldBreak = false;
            for (const auto& pair : freq) {
                if (pair.second > (n - i) / distinctCount) {
                    shouldBreak = true;
                    break;
                }
            }
            if (shouldBreak) break;
        }
    }
    
    return maxLength;
}

// Alternative approach for very large inputs - using frequency-based iteration
int longestBalancedSubarrayOptimized(vector<int>& arr) {
    int n = arr.size();
    int maxLength = 1;
    
    // For each possible target frequency
    for (int targetFreq = 1; targetFreq <= n / 2; targetFreq++) {
        
        for (int start = 0; start < n; start++) {
            unordered_map<int, int> freq;
            int validElements = 0; // Elements with exactly targetFreq occurrences
            
            for (int end = start; end < n; end++) {
                freq[arr[end]]++;
                
                if (freq[arr[end]] == targetFreq) {
                    validElements++;
                } else if (freq[arr[end]] == targetFreq + 1) {
                    validElements--;
                }
                
                // If any element exceeds targetFreq, this path is invalid
                if (freq[arr[end]] > targetFreq) {
                    break;
                }
                
                // Check if current subarray is balanced
                int subarrayLength = end - start + 1;
                int distinctCount = freq.size();
                
                if (validElements == distinctCount && distinctCount * targetFreq == subarrayLength) {
                    maxLength = max(maxLength, subarrayLength);
                }
            }
        }
    }
    
    return maxLength;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Use optimized version for larger inputs
    if (n > 1000) {
        cout << longestBalancedSubarrayOptimized(arr) << endl;
    } else {
        cout << longestBalancedSubarray(arr) << endl;
    }
    
    return 0;
}
