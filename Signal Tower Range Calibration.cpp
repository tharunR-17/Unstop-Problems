#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> X(N), Th(N);

    for (int i = 0; i < N; i++) cin >> X[i];

    long long low = 0;
    for (int i = 0; i < N; i++) {
        cin >> Th[i];
        low = max(low, Th[i]);
    }

    long long high = 5000000000LL;

    auto ok = [&](long long P) {
        long long L = LLONG_MIN / 4;
        long long R = LLONG_MAX / 4;

        for (int i = 0; i < N; i++) {
            if (P < Th[i]) return false;
            long long d = P - Th[i];
            L = max(L, X[i] - d);
            R = min(R, X[i] + d);
            if (L > R) return false;
        }

        return true;
    };

    while (low < high) {
        long long mid = low + (high - low) / 2;
        if (ok(mid))
            high = mid;
        else
            low = mid + 1;
    }

    cout << low << '\n';

    return 0;
}
