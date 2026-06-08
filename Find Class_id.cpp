#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Input the size of the array
    int n;
    cin >> n;

    // Input the array
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Iterate through the array to find the peak element
    for (int i = 0; i < n; i++) {
        // Handle edge cases and middle elements
        if ((i == 0 || arr[i] >= arr[i - 1]) && (i == n - 1 || arr[i] >= arr[i + 1])) {
            cout << i << endl; // Print the class_id
            return 0;
        }
    }

    return 0; // This should never be reached for a valid mountain array
}
