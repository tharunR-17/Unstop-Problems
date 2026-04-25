#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

/**
 * Logic:
 * 1. Store Unique Drivers: Use a set<int> to automatically handle duplicates.
 * 2. Restaurant Frequency: Use a map<string, int> to count occurrences of each name.
 * 3. Max Popularity: Calculate (length * score) for each entry and maintain a running maximum.
 */

int main() {
    int N;
    if (!(cin >> N)) return 0;

    set<int> uniqueDrivers;
    map<string, int> restaurantCount;
    int maxPopularity = 0;

    for (int i = 0; i < N; ++i) {
        int driverId;
        string restaurantName;
        int baseRating;

        cin >> driverId >> restaurantName >> baseRating;

        // Task 1: Track unique drivers
        uniqueDrivers.insert(driverId);

        // Task 2: Track restaurant frequency
        restaurantCount[restaurantName]++;

        // Task 3: Calculate popularity score
        // Popularity = (Number of letters in name) * (Base rating)
        int popularity = restaurantName.length() * baseRating;
        if (popularity > maxPopularity) {
            maxPopularity = popularity;
        }
    }

    // Determine the most frequent restaurant
    string mostFrequentRestaurant = "";
    int maxFrequency = -1;

    for (auto const& [name, count] : restaurantCount) {
        if (count > maxFrequency) {
            maxFrequency = count;
            mostFrequentRestaurant = name;
        }
    }

    // Output the results
    cout << uniqueDrivers.size() << endl;
    cout << mostFrequentRestaurant << endl;
    cout << maxPopularity << endl;

    return 0;
}
