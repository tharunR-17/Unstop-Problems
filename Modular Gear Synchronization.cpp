#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> a(n), f(n);
    ll L = 1;
    const ll LIMIT = 1e15;

    for (int i = 0; i < n; i++) {
        cin >> a[i] >> f[i];
        ll g = gcd(L, a[i]);
        if (L > LIMIT / (a[i] / g)) {
            cout << -1 << '\n';
            return 0;
        }
        L = L * (a[i] / g);
    }

    for (int i = 0; i < n; i++) {
        if (L % f[i] == 0) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << L << '\n';
    return 0;
}
