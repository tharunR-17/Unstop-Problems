#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    unordered_map<int, long long> mp;
    mp[0] = 1;

    int xr = 0;
    long long ans = 0;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        xr ^= x;
        ans += mp[xr ^ K];
        mp[xr]++;
    }

    cout << ans << '\n';

    return 0;
}
