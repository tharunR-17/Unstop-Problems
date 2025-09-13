#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Function to check if the array is sorted
bool isSorted(const vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Function to count the minimum shifts needed to sort the array
int countShifts(vector<int> arr) {
    int n = arr.size();
    int count = 0;
    int i = 0;

    while (i < n - 1) {
        if (arr[i] <= arr[i + 1]) {
            i++;
        } else {
            int j = i;
            while (j < n - 1 && arr[j] > arr[j + 1]) {
                j++;
            }
            count++;
            // Simulate the shift
            int temp = arr[i];
            for (int k = i; k < j; k++) {
                arr[k] = arr[k + 1];
            }
            arr[j] = temp;
            i = max(i - 1, 0);
        }
    }
    return count;
}

// Main function to calculate minimum shifts
int minShifts(vector<int>& A) {
    int n = A.size();
    if (isSorted(A)) {
        return 0;
    }

    vector<int> bad;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            bad.push_back(i);
        }
    }

    if (bad.size() > 5) {
        return -1; // Too many wrong places, cannot fix with 1 swap
    }

    int ans = INT_MAX;

    // Try no swap
    ans = min(ans, countShifts(A));

    // Try swapping bad positions and their neighbors
    for (int idx : bad) {
        for (int j = 0; j < n; j++) {
            if (idx == j) continue;

            vector<int> temp = A;
            swap(temp[idx], temp[j]);

            if (isSorted(temp)) return 0;

            int shifts = countShifts(temp);
            ans = min(ans, shifts);
        }
    }

    return (ans == INT_MAX) ? -1 : ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    cout << minShifts(A) << endl;

    return 0;
}
