#include <iostream>
#include <vector>
#include <numeric>
#include <cstring>

using namespace std;

// Backtracking function to try forming subsets
bool backtrack(vector<int>& arr, vector<bool>& visited, int k, int targetSum, int startIndex, int currentSum, int currentCount);

// Helper function to check if it's possible to partition the array into k subsets
bool canPartitionKSubsets(vector<int>& arr, int k) {
    int totalSum = 0;
    
    // Step 1: Calculate the total sum of the array
    for (int num : arr) {
        totalSum += num;
    }

    // Step 2: If the total sum is not divisible by k, it's not possible to partition
    if (totalSum % k != 0) {
        return false;
    }

    int targetSum = totalSum / k;
    vector<bool> visited(arr.size(), false); // Array to track visited elements
    
    // Step 3: Try to partition the array into k subsets
    return backtrack(arr, visited, k, targetSum, 0, 0, 0);
}

// Backtracking function to try forming subsets
bool backtrack(vector<int>& arr, vector<bool>& visited, int k, int targetSum, int startIndex, int currentSum, int currentCount) {
    // If we have formed k-1 subsets, the remaining elements must form the last subset
    if (k == 1) {
        return true;
    }
    
    // If the current sum is equal to the target sum, start forming the next subset
    if (currentSum == targetSum) {
        return backtrack(arr, visited, k - 1, targetSum, 0, 0, currentCount);
    }
    
    // Try to form the current subset
    for (int i = startIndex; i < arr.size(); i++) {
        // Skip already visited elements or elements that will cause the sum to exceed the target
        if (visited[i] || currentSum + arr[i] > targetSum) {
            continue;
        }

        // Mark the element as visited
        visited[i] = true;
        
        // Recursively try to add the element to the current subset
        if (backtrack(arr, visited, k, targetSum, i + 1, currentSum + arr[i], currentCount + 1)) {
            return true;
        }
        
        // Backtrack, unmark the element
        visited[i] = false;
    }

    return false;
}

int main() {
    // Input
    string input;
    getline(cin, input); // Read array as a string
    int k;
    cin >> k; // Read value of k
    
    // Convert input string into integer array
    vector<int> arr;
    size_t pos = 0;
    while ((pos = input.find(' ')) != string::npos) {
        arr.push_back(stoi(input.substr(0, pos)));
        input.erase(0, pos + 1);
    }
    arr.push_back(stoi(input)); // For the last element
    
    // Check if it's possible to partition the array into k subsets
    if (canPartitionKSubsets(arr, k)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
