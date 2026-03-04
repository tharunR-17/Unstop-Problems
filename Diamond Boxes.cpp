#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// Function to check if it's possible to transfer all diamonds with a given maxBoxes
bool canTransfer(const vector<int>& diamonds, int maxBoxes, int trips) {
    int currentSum = 0;
    int currentTrips = 1;

    for (int diamond : diamonds) {
        if (diamond > maxBoxes) {
            return false; // If a single pouch has more diamonds than maxBoxes
        }

        if (currentSum + diamond > maxBoxes) {
            currentTrips++;
            currentSum = diamond;
            if (currentTrips > trips) {
                return false;
            }
        } else {
            currentSum += diamond;
        }
    }

    return true;
}

// Function to find the minimum number of diamond boxes
int minimumDiamondBoxes(vector<int>& diamonds, int trips) {
    int low = 1;
    int high = accumulate(diamonds.begin(), diamonds.end(), 0); // Sum of all diamonds
    int result = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canTransfer(diamonds, mid, trips)) {
            result = mid; // Update result
            high = mid - 1; // Try for a lower value
        } else {
            low = mid + 1; // Increase the value
        }
    }

    return result;
}

int main() {
    int n, t;
    cin >> n;

    vector<int> diamonds(n);
    for (int i = 0; i < n; i++) {
        cin >> diamonds[i];
    }

    cin >> t;

    cout << minimumDiamondBoxes(diamonds, t) << endl;

    return 0;
}
