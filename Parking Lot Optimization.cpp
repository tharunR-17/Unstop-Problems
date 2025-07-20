#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int minParkingSpots(vector<pair<int, int>>& cars) {
    sort(cars.begin(), cars.end());
    priority_queue<int, vector<int>, greater<int>> pq;

    int maxSpots = 0;
    for (auto& car : cars) {
        int arrival = car.first;
        int departure = arrival + car.second;

        while (!pq.empty() && pq.top() <= arrival) {
            pq.pop();
        }

        pq.push(departure);
        maxSpots = max(maxSpots, (int)pq.size());
    }

    return maxSpots;
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> cars(n);
    for (int i = 0; i < n; i++) {
        cin >> cars[i].first >> cars[i].second;
    }

    cout << minParkingSpots(cars) << endl;
    return 0;
}
