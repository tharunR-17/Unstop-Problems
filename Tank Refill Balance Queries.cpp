#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> prefix(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        long long x;
        cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int L, R;
        cin >> L >> R;

        long long sum = prefix[R] - prefix[L - 1];

        if (sum > 0)
            cout << sum << " SURPLUS\n";
        else if (sum < 0)
            cout << sum << " DEFICIT\n";
        else
            cout << sum << " BALANCED\n";
    }

    return 0;
}
