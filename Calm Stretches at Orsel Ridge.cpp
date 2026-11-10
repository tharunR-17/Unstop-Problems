#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    long long K;
    if (!(cin >> n >> q >> K)) return 0;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> L(n + 1);
    deque<int> max_dq, min_dq;
    int left = 1;

    for (int i = 1; i <= n; ++i) {
        while (!max_dq.empty() && a[max_dq.back()] <= a[i]) {
            max_dq.pop_back();
        }
        max_dq.push_back(i);

        while (!min_dq.empty() && a[min_dq.back()] >= a[i]) {
            min_dq.pop_back();
        }
        min_dq.push_back(i);

        while (a[max_dq.front()] - a[min_dq.front()] > K) {
            left++;
            if (max_dq.front() < left) max_dq.pop_front();
            if (min_dq.front() < left) min_dq.pop_front();
        }
        L[i] = left;
    }

    vector<int> C(n + 1);
    vector<long long> prefC(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        C[i] = i - L[i] + 1;
        prefC[i] = prefC[i - 1] + C[i];
    }

    int log_n = log2(n) + 1;
    vector<vector<int>> st(n + 1, vector<int>(log_n));
    for (int i = 1; i <= n; ++i) {
        st[i][0] = C[i];
    }
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    auto query_max = [&](int l, int r) {
        if (l > r) return 0;
        int j = log2(r - l + 1);
        return max(st[l][j], st[r - (1 << j) + 1][j]);
    };

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;

        // Binary search to find the first index p where L[p] > l
        int p = upper_bound(L.begin() + l, L.begin() + r + 1, l) - L.begin();

        long long total_stretches = 0;
        int max_len = 0;

        long long cnt = p - l;
        if (cnt > 0) {
            total_stretches += cnt * (cnt + 1) / 2;
            max_len = max(max_len, (int)cnt);
        }

        if (p <= r) {
            total_stretches += prefC[r] - prefC[p - 1];
            max_len = max(max_len, query_max(p, r));
        }

        cout << total_stretches << " " << max_len << "\n";
    }

    return 0;
}
