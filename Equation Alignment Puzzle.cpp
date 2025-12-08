#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    int n;
    cin >> n;

    vector<pair<ll, ll>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    ll a, b, c;
    cin >> a >> b >> c;

    int count = 0;

    for (int i = 0; i < n; ++i) {
        ll x = points[i].first;
        ll y = points[i].second;

        ll expected_y = a * x * x + b * x + c;

        if (expected_y == y) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}
