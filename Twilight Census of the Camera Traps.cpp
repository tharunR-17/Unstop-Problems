#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll W;
    cin >> n >> W;

    queue<pair<ll, ll>> window;
    unordered_map<ll, int> freq;

    int distinct = 0;
    int peak = 0;
    ll earliestTime = 0;

    for (int i = 0; i < n; i++) {
        ll minute, species;
        cin >> minute >> species;

        // Add current record
        window.push({minute, species});

        if (freq[species] == 0) {
            distinct++;
        }

        freq[species]++;

        // Remove expired records
        while (!window.empty() &&
               window.front().first <= minute - W) {

            ll oldSpecies = window.front().second;
            window.pop();

            freq[oldSpecies]--;

            if (freq[oldSpecies] == 0) {
                distinct--;
                freq.erase(oldSpecies);
            }
        }

        // Update maximum variety
        if (distinct > peak) {
            peak = distinct;
            earliestTime = minute;
        }
    }

    cout << "PEAK " << peak << " AT " << earliestTime << '\n';

    return 0;
}
