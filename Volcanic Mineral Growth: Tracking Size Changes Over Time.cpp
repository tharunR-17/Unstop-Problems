#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to compute the final sizes of minerals after D days
vector<long long> computeFinalSizes(int numMinerals, vector<int>& initialSizes, int numDays) {
    vector<long long> finalSizes(numMinerals);

    long long num = 1, den = 1;

    for (int day = 1; day <= numDays; day++) {
        if (day % 3 == 0) {
            den *= 2;
        } else {
            num *= 2;
        }
        
        long long a = num, b = den;
        while (b) { long long t = b; b = a % b; a = t; }
        num /= a;
        den /= a;
    }

    for (int i = 0; i < numMinerals; i++) {
        finalSizes[i] = ((long long)initialSizes[i] * num) / den;
    }

    return finalSizes;
}

int main() {
    int numMinerals, numDays;
    cin >> numMinerals;
    vector<int> initialSizes(numMinerals);
    for (int i = 0; i < numMinerals; ++i) {
        cin >> initialSizes[i];
    }
    cin >> numDays;

    // Get the final sizes of the minerals after the specified number of days
    vector<long long> result = computeFinalSizes(numMinerals, initialSizes, numDays);

    // Output the final sizes
    for (long long size : result) {
        cout << size << " ";
    }
    cout << endl;

    return 0;
}
