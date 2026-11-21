#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

void solve() {
    int N;
    long long T;
    cin >> N >> T;

    unordered_map<int, int> freq;
    queue<pair<long long, int>> q;

    vector<int> ans(N);

    int distinct = 0;
    int maxDistinct = 0;
    long long bestMinute = 0;

    for (int i = 0; i < N; i++) {
        long long minute;
        int badge;

        cin >> minute >> badge;

        // Insert current scan
        q.push({minute, badge});

        freq[badge]++;

        if (freq[badge] == 1) {
            distinct++;
        }

        // Remove expired scans
        long long earliest = minute - T + 1;

        while (!q.empty() && q.front().first < earliest) {
            int oldBadge = q.front().second;
            q.pop();

            freq[oldBadge]--;

            if (freq[oldBadge] == 0) {
                distinct--;
                freq.erase(oldBadge);
            }
        }

        // Store current indicator
        ans[i] = distinct;

        // Update maximum and earliest minute
        if (distinct > maxDistinct) {
            maxDistinct = distinct;
            bestMinute = minute;
        }
    }

    // Output headline
    cout << maxDistinct << " " << bestMinute << "\n";

    // Output all indicator values
    for (int i = 0; i < N; i++) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }

    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
