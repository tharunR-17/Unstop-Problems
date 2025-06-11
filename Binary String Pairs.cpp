#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
ll solve(const int n, const string &s, const char ch) {
    int m = 0;
    while ((1 << m) < n) ++m;
    vector<ll> dp(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == ch) {
            ++dp[i];
        }
    }
    ll ans = 0;
    for (int i = 0; i < m; ++i) {
        for (int mask = 0; mask < n; ++mask) {
            if (mask >> i & 1) {
                dp[mask] += 2 * dp[mask ^ (1 << i)];
            }
        }
    }
    for (int mask = 0; mask < n; ++mask) {
        if (s[mask] == ch)
            ans += dp[mask];
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    ll res = solve(n, s, '0') + solve(n, s, '1');
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
