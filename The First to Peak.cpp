#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>

using namespace std;

void solve(int N, int K, vector<int>& sensor,
           vector<int>& temperature) {
    deque<int> dq;
    unordered_map<int, int> credits;

    for (int i = 0; i < N; i++) {
        // Remove indices outside the current window
        while (!dq.empty() && dq.front() <= i - K) {
            dq.pop_front();
        }

        // Remove only strictly smaller temperatures.
        // Equal temperatures stay to preserve the earliest peak.
        while (!dq.empty() &&
               temperature[dq.back()] < temperature[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Count the winner once a complete window exists
        if (i >= K - 1) {
            int winner = dq.front();
            credits[sensor[winner]]++;
        }
    }

    vector<pair<int, int>> result;

    for (const auto& entry : credits) {
        result.push_back({entry.first, entry.second});
    }

    sort(result.begin(), result.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) {
             if (a.second != b.second) {
                 return a.second > b.second;
             }
             return a.first < b.first;
         });

    cout << result.size() << '\n';

    for (const auto& entry : result) {
        cout << entry.first << ' '
             << entry.second << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> sensor(N);
    vector<int> temperature(N);

    for (int i = 0; i < N; i++) {
        cin >> sensor[i] >> temperature[i];
    }

    solve(N, K, sensor, temperature);

    return 0;
}
