#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long C;
    cin >> N >> C;

    vector<long long> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // If no trees, no steps needed
    if (N == 0) {
        cout << 0 << "\n";
        return 0;
    }

    long long steps = 0;
    long long remaining = C;
    int pos = -1;  // starting position

    for (int i = 0; i < N; i++) {
        // If we cannot collect this tree with remaining capacity,
        // go back to start (-1)
        if (remaining < arr[i]) {
            steps += abs(pos - (-1));
            pos = -1;
            remaining = C;
        }

        // Walk from current position to tree i
        steps += abs(i - pos);
        pos = i;

        // Collect apples
        remaining -= arr[i];
    }

    cout << steps << "\n";
    return 0;
}
