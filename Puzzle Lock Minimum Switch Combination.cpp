#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<int> mask(M);
    for (int i = 0; i < M; i++)
        cin >> mask[i];

    int S, T;
    cin >> S >> T;

    int need = S ^ T;
    int total = 1 << M;

    vector<int> xr(total, 0);

    int ans = INT_MAX;

    for (int subset = 1; subset < total; subset++) {
        int bit = __builtin_ctz(subset);
        int prev = subset & (subset - 1);
        xr[subset] = xr[prev] ^ mask[bit];

        if (xr[subset] == need) {
            ans = min(ans, __builtin_popcount(subset));
        }
    }

    if (need == 0) ans = 0;

    cout << (ans == INT_MAX ? -1 : ans);
    return 0;
}
