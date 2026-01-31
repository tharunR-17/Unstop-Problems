#include <bits/stdc++.h>
using namespace std;

struct Villager {
    int start;
    int end;
};

int maxVillagers(int N, int K, int T, vector<Villager>& villagers) {
    vector<pair<int,int>> intervals;

    // Convert to valid start intervals
    for (auto &v : villagers) {
        int latestStart = v.end - T;
        if (latestStart >= v.start) {
            intervals.push_back({v.start, latestStart});
        }
    }

    // Sort by earliest latestStart (deadline)
    sort(intervals.begin(), intervals.end(),
         [](auto &a, auto &b) {
             return a.second < b.second;
         });

    vector<int> timeline(1440, 0);
    int count = 0;

    for (auto &iv : intervals) {
        for (int s = iv.first; s <= iv.second; s++) {
            bool canAssign = true;

            for (int t = s; t < s + T; t++) {
                if (timeline[t] >= K) {
                    canAssign = false;
                    break;
                }
            }

            if (canAssign) {
                for (int t = s; t < s + T; t++) {
                    timeline[t]++;
                }
                count++;
                break;
            }
        }
    }

    return count;
}

int main() {
    int N, K, T;
    cin >> N >> K >> T;

    vector<Villager> villagers(N);
    for (int i = 0; i < N; i++) {
        cin >> villagers[i].start >> villagers[i].end;
    }

    cout << maxVillagers(N, K, T, villagers);
    return 0;
}
