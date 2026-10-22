#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class FenwickTree {
    int n;
    vector<int> bit;

public:
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};

void solve(int q, long long D, vector<pair<int, int>>& reports) {
    vector<int> temps;

    for (auto& r : reports) {
        temps.push_back(r.second);
    }

    sort(temps.begin(), temps.end());
    temps.erase(unique(temps.begin(), temps.end()), temps.end());

    FenwickTree bit(temps.size());
    unordered_map<int, int> lastTemp;

    for (auto& r : reports) {
        int id = r.first;
        int temp = r.second;

        int rank = lower_bound(temps.begin(), temps.end(), temp)
                   - temps.begin() + 1;

        auto it = lastTemp.find(id);

        if (it != lastTemp.end()) {
            int oldTemp = it->second;

            if (abs((long long)temp - oldTemp) > D) {
                bit.update(
                    lower_bound(temps.begin(), temps.end(), oldTemp)
                    - temps.begin() + 1,
                    -1
                );

                int count = bit.query(rank - 1);
                cout << id << " " << temp << " " << count << '\n';

                bit.update(
                    lower_bound(temps.begin(), temps.end(), oldTemp)
                    - temps.begin() + 1,
                    1
                );
            }

            bit.update(
                lower_bound(temps.begin(), temps.end(), oldTemp)
                - temps.begin() + 1,
                -1
            );
        }

        bit.update(rank, 1);
        lastTemp[id] = temp;
    }
}

int main() {
    int q;
    long long D;
    cin >> q >> D;

    vector<pair<int, int>> reports(q);

    for (int i = 0; i < q; i++) {
        cin >> reports[i].first >> reports[i].second;
    }

    solve(q, D, reports);

    return 0;
}
