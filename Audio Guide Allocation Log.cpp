#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>
using namespace std;

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    // Available devices: smallest device number first
    priority_queue<int, vector<int>, greater<int>> available;

    // Busy devices: earliest availability time first
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > busy;

    vector<int> answer(n);

    int nextDevice = 1;

    for (int i = 0; i < n; i++) {
        long long arrival, duration;
        cin >> arrival >> duration;

        // Release all devices whose sanitisation is complete
        while (!busy.empty() && busy.top().first <= arrival) {
            available.push(busy.top().second);
            busy.pop();
        }

        int device;

        // Use the smallest available device
        if (!available.empty()) {
            device = available.top();
            available.pop();
        }
        else {
            device = nextDevice++;
        }

        answer[i] = device;

        // Calculate when the device becomes available again
        long long releaseTime = arrival + duration + k;

        busy.push({releaseTime, device});
    }

    // Print assigned device numbers
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << answer[i];
    }

    cout << '\n';

    // Print total distinct devices used
    cout << nextDevice - 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
