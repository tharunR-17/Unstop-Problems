#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> PeakMax_Distinct_readings(
    vector<int>& readings, int n, int W) {

    vector<pair<int, int>> ans;

    deque<int> dq;
    unordered_map<int, int> freq;

    // First window
    for (int i = 0; i < W; i++) {

        // Maintain decreasing deque
        while (!dq.empty() &&
               readings[dq.back()] <= readings[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Frequency for distinct count
        freq[readings[i]]++;
    }

    // First window result
    ans.push_back({
        readings[dq.front()],
        (int)freq.size()
    });

    // Slide the window
    for (int i = W; i < n; i++) {

         freq[readings[i]]++;
         // Maintain decreasing deque
        while (!dq.empty() &&
               readings[dq.back()] <= readings[i]) {
            dq.pop_back();
        }
         dq.push_back(i);

        int outgoing = readings[i - W];

        // Remove outgoing element from frequency
        freq[outgoing]--;

        if (freq[outgoing] == 0) {
            freq.erase(outgoing);
        }

        // Remove indices outside current window
        while (!dq.empty() && dq.front() <= i - W) {
            dq.pop_front();
        }
        // Store answer
        ans.push_back({
            readings[dq.front()],
            (int)freq.size()
        });
    }

    return ans;
}

int main() {
    int n, W;
    cin >> n >> W;

    vector<int> readings(n);

    for (int i = 0; i < n; i++) {
        cin >> readings[i];
    }

    vector<pair<int, int>> ans =
        PeakMax_Distinct_readings(readings, n, W);

    for (auto& p : ans) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
