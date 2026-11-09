#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


#include <bits/stdc++.h>
using namespace std;

struct Train {
    int t;   
    int p;   
    int d; 
};

int toMinutes(const string& s) {
    int h = (s[0] - '0') * 10 + (s[1] - '0');
    int m = (s[3] - '0') * 10 + (s[4] - '0');
    return h * 60 + m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    if (!(cin >> n >> W)) return 0;

    vector<Train> trains;
    trains.reserve(n);
    vector<string> rawTimes;
    rawTimes.reserve(n);

    for (int i = 0; i < n; ++i) {
        string timeStr;
        int p, d;
        cin >> timeStr >> p >> d;
        rawTimes.push_back(timeStr);
        trains.push_back({toMinutes(timeStr), p, d});
    }

    multiset<int> activeLateness;                 
    unordered_map<int, int> platformCount;        
    int distinctPlatforms = 0;

    int left = 0;
    long long maxPressure = -1;
    int bestIdx = -1;

    for (int right = 0; right < n; ++right) {
        int curD = trains[right].d;
        int curP = trains[right].p;
        activeLateness.insert(curD);
        if (++platformCount[curP] == 1) {
            ++distinctPlatforms;
        }
        int threshold = trains[right].t - W;
        while (left <= right && trains[left].t <= threshold) {
            int oldD = trains[left].d;
            int oldP = trains[left].p;

            auto it = activeLateness.find(oldD);
            if (it != activeLateness.end()) {
                activeLateness.erase(it);
            }

            if (--platformCount[oldP] == 0) {
                platformCount.erase(oldP);
                --distinctPlatforms;
            }
            ++left;
        }
        long long maxLate = activeLateness.empty() ? 0 : *activeLateness.rbegin();
        long long pressure = maxLate * (long long)distinctPlatforms;

        if (pressure > maxPressure) {
            maxPressure = pressure;
            bestIdx = right;
        }
    }

    cout << maxPressure << " " << rawTimes[bestIdx] << "\n";
    return 0;
}
