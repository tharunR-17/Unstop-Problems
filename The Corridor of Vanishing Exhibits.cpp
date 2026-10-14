#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FenwickTree {
    int n;
    vector<int> bit;

public:
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}

    void update(int idx, int delta) {
        while (idx <= n) {
            bit[idx] += delta;
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

    // Find the position of the k-th active element.
    int kth(int k) {
        int idx = 0;
        int step = 1;

        while (step * 2 <= n) {
            step *= 2;
        }

        for (; step > 0; step /= 2) {
            int next = idx + step;

            if (next <= n && bit[next] < k) {
                idx = next;
                k -= bit[next];
            }
        }

        return idx + 1;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> value(n + 1);
    vector<pair<int, int>> sortedValues;

    for (int i = 1; i <= n; i++) {
        cin >> value[i];
        sortedValues.push_back({value[i], i});
    }

    sort(sortedValues.begin(), sortedValues.end());

    vector<int> rankOf(n + 1);

    for (int i = 0; i < n; i++) {
        rankOf[sortedValues[i].second] = i + 1;
    }

    FenwickTree positions(n);
    FenwickTree values(n);

    for (int i = 1; i <= n; i++) {
        positions.update(i, 1);
        values.update(rankOf[i], 1);
    }

    int m;
    cin >> m;

    while (m--) {
        char type;
        int x;
        cin >> type >> x;

        if (type == 'R') {
            positions.update(x, -1);
            values.update(rankOf[x], -1);
        }
        else if (type == 'N') {
            int leftCount = positions.query(x - 1);
            int totalLeft = leftCount;

            int left = -1;
            int right = -1;

            if (totalLeft > 0) {
                left = positions.kth(totalLeft);
            }

            int throughX = positions.query(x);
            int total = positions.query(n);

            if (throughX < total) {
                right = positions.kth(throughX + 1);
            }

            cout << left << " " << right << '\n';
        }
        else if (type == 'K') {
            int total = values.query(n);

            if (x > total) {
                cout << "-1 -1\n";
            } else {
                int rank = values.kth(total - x + 1);
                int artifactValue = sortedValues[rank - 1].first;
                int pedestal = sortedValues[rank - 1].second;

                cout << artifactValue << " " << pedestal << '\n';
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
