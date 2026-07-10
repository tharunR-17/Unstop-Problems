#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    long long ans = 0;
    for (int i = 0; i < N; i++) {
        long long x;
        cin >> x;
        ans ^= x;
    }

    cout << ans;

    return 0;
}
