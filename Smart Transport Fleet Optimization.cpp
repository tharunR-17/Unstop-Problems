#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Shipment {
    int pickup;
    int delivery;
    int reward;
};

int calculateMaxReward(int numTrucks, int numShipments, vector<int>& truckLimits, vector<Shipment>& shipments) {
    // User logic goes here
    vector<pair<int,int>> ships(numShipments);
    for (int i = 0; i < numShipments; i++) {
        int p = shipments[i].pickup;
        int d = shipments[i].delivery;
        int dist = p + abs(p - d) + d;
        ships[i] = {dist, shipments[i].reward};
    }

    sort(truckLimits.begin(), truckLimits.end());
    sort(ships.begin(), ships.end());

    vector<vector<int>> dp(numTrucks + 1, vector<int>(numShipments + 1, 0));

    for (int i = 1; i <= numTrucks; i++) {
        for (int j = 1; j <= numShipments; j++) {
            dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            if (ships[j-1].first <= truckLimits[i-1]) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + ships[j-1].second);
            }
        }
    }

    return dp[numTrucks][numShipments];
}

int main() {
    int numTrucks, numShipments;
    cin >> numTrucks >> numShipments;

    vector<int> truckLimits(numTrucks);
    for (int i = 0; i < numTrucks; ++i) {
        cin >> truckLimits[i];
    }

    vector<Shipment> shipments(numShipments);
    for (int i = 0; i < numShipments; ++i) {
        int pickup, delivery, reward;
        cin >> pickup >> delivery >> reward;
        shipments[i] = {pickup, delivery, reward};
    }

    int maxReward = calculateMaxReward(numTrucks, numShipments, truckLimits, shipments);

    cout << maxReward << endl;

    return 0;
}
