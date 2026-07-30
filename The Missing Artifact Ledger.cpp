#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long ans = 0, x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        ans ^= x;
    }

    cout << ans;
    return 0;
}
