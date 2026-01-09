#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Placeholder function for user logic
int computeTotalTime(int N, const vector<int>& fabric, const vector<int>& temp) {
    // User should implement their logic here
    // Parameters:
    // N: number of clothes
    // fabric: vector of fabric types
    // temp: vector of temperatures
    // Return: total time in units
   // return 0; // Placeholder return value
      if (N == 0) return 0;

    int totalTime = 1;  // Time for the first cloth

    for (int i = 1; i < N; ++i) {
        totalTime += 1;  // Pressing time for current cloth

        // If fabric type changes, add temperature adjustment time
        if (fabric[i] != fabric[i - 1]) {
            totalTime += abs(temp[i] - temp[i - 1]);
        }
    }

    return totalTime;
}

int main() {
    int N;
    cin >> N;
    
    vector<int> fabric(N);
    vector<int> temp(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> fabric[i];
    }
    
    for (int i = 0; i < N; ++i) {
        cin >> temp[i];
    }
    
    // Call user logic function and print the output
    int totalTime = computeTotalTime(N, fabric, temp);
    cout << totalTime << endl;
    
    return 0;
}
