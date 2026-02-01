#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<long long> H(N);
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }

    long long max_so_far = 0;
    int valid = 0;

    for (int i = 0; i < N; i++) {
        if (H[i] > max_so_far) {
            valid++;
            max_so_far = H[i];
        }
    }

    cout << min(valid, K) << endl;
    return 0;
}
