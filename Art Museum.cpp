#include <bits/stdc++.h>
using namespace std;

long long solve(vector<int> x) {
    sort(x.begin(), x.end());
    return x[x.size() / 2] - x[(x.size() - 1) / 2] + 1;
}

void solve() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];
    cout << solve(x) * solve(y) << '\n';
}

signed main(){ 
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    // #ifndef ONLINE_JUDGE
    // freopen("IO files/Edge_input (1).txt", "r", stdin);
    // freopen("IO files/Edge_output (1).txt", "w", stdout);
    // #endif

    solve();
    return 0;
}
