#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegTree {
    int n;
    vector<ll> t;
    ll NEG = LLONG_MIN / 4;
    SegTree(int sz) {
        n = 1;
        while (n < sz) n <<= 1;
        t.assign(2 * n, NEG);
    }
    void update(int pos, ll val) {
        pos += n;
        t[pos] = max(t[pos], val);
        pos >>= 1;
        while (pos) {
            t[pos] = max(t[pos << 1], t[(pos << 1) | 1]);
            pos >>= 1;
        }
    }
    ll query(int l, int r) {
        if (l > r) return NEG;
        l += n; r += n;
        ll res = NEG;
        while (l <= r) {
            if (l & 1) res = max(res, t[l++]);
            if (!(r & 1)) res = max(res, t[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    vector<ll> nums(N);
    for (int i = 0; i < N; ++i) cin >> nums[i];
    ll diff;
    cin >> diff;
    vector<ll> vals = nums;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int M = (int)vals.size();
    SegTree seg0(M), seg1(M);
    ll answer = LLONG_MIN;
    for (int i = 0; i < N; ++i) {
        ll v = nums[i];
        ll leftVal = v - diff;
        ll rightVal = v + diff;
        int L = int(lower_bound(vals.begin(), vals.end(), leftVal) - vals.begin());
        int R = int(upper_bound(vals.begin(), vals.end(), rightVal) - vals.begin()) - 1;
        ll best0_in = seg0.query(L, R);
        ll best1_in = seg1.query(L, R);
        ll dp0 = v + max(0LL, best0_in == seg0.NEG ? 0LL : best0_in);
        ll best0_left = seg0.query(0, L - 1);
        ll best0_right = seg0.query(R + 1, M - 1);
        ll best0_out = max(best0_left, best0_right);
        ll cand_extend_dp1 = v + max(0LL, best1_in == seg1.NEG ? 0LL : best1_in);
        ll cand_bridge = seg0.NEG;
        if (best0_out != seg0.NEG) cand_bridge = v + best0_out;
        ll dp1 = dp0;
        dp1 = max(dp1, cand_extend_dp1);
        if (cand_bridge != seg0.NEG) dp1 = max(dp1, cand_bridge);
        int idx = int(lower_bound(vals.begin(), vals.end(), v) - vals.begin());
        seg0.update(idx, dp0);
        seg1.update(idx, dp1);
        answer = max(answer, max(dp0, dp1));
    }
    cout << answer << '\n';
    return 0;
}
