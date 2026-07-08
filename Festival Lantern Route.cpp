#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N;
    long long D;
    cin >> N >> D;

    vector<long long> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int ans = 1;
    long long last = a[0];

    for (int i = 1; i < N; i++) {
        if (a[i] - last >= D) {
            ans++;
            last = a[i];
        }
    }

    cout << ans;
    return 0;
}
