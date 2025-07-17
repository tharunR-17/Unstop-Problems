#include <iostream>
#include <vector>

using namespace std;

// Placeholder function for user logic
int min_operations(int n, const vector<int>& E, const vector<int>& T) {
    vector<int>required(n);

    for(int i = 0 ; i < n ; i++){
        required[i] =  T[i] - E[i];
    }
       int moves = 0;
    //int n = required.size();

    int i = 0;
    while (i < n) {
        if (required[i] == 0) {
            i++;
            continue;
        }

        int sign = (required[i] > 0) ? 1 : -1;
        int maxel = abs(required[i]);

        int j = i + 1;
        while (j < n && required[j] * sign > 0) {
            maxel = max(maxel, abs(required[j]));
            j++;
        }

        moves += maxel;
        i = j; // Move to next segment
    }

    return moves;
}

int main() {
    int n;
    cin >> n; // Read the number of sectors 

    vector<int> E(n); // Vector to store initial energy levels
    vector<int> T(n); // Vector to store required energy thresholds

    for (int i = 0; i < n; ++i) {
        cin >> E[i]; // Read initial energy levels
    }

    for (int i = 0; i < n; ++i) {
        cin >> T[i]; // Read required energy thresholds
    }

    // Call the user logic function
    int result = min_operations(n, E, T);

    // Print the result
    cout << result << endl;

    return 0;
}
