#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> A(N + 1), pref(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        pref[i] = pref[i - 1] + A[i];
    }

    for (int i = 1; i <= N; i++) {
        long long leftSum = pref[i - 1];
        long long rightSum = pref[N] - pref[i];

        if (leftSum == rightSum) {
            cout << i << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
