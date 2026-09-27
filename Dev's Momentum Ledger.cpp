#include <bits/stdc++.h>
using namespace std;

class Fenwick {
    int n;
    vector<int> bit;

public:
    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    int sum(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    int rangeSum(int l, int r) const {
        if (l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long K;
    cin >> n >> K;

    vector<long long> a(n);
    for (auto &x : a)
        cin >> x;

    // Coordinate compression of all scores.
    vector<long long> coords = a;
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    Fenwick fw(coords.size());

    for (int i = 0; i < n; i++) {
        long long x = a[i];

        // We need previous scores in [x-K, x+K].
        long long low = x - K;
        long long high = x + K;

        // First coordinate >= low.
        int left = lower_bound(coords.begin(), coords.end(), low)
                   - coords.begin() + 1;

        // Last coordinate <= high.
        int right = upper_bound(coords.begin(), coords.end(), high)
                    - coords.begin();

        int answer = fw.rangeSum(left, right);

        cout << answer << '\n';

        // Add today's score only AFTER querying,
        // because today's score must not count itself.
        int pos = lower_bound(coords.begin(), coords.end(), x)
                  - coords.begin() + 1;

        fw.add(pos, 1);
    }

    return 0;
}
