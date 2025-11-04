#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll modAdd(ll x, ll y, ll mod) {
    return ((x % mod) + (y % mod)) % mod;
}

ll modSub(ll x, ll y, ll mod) {
    return ((x + mod) % mod - (y + mod) % mod) % mod;
}

ll modMul(ll x, ll y, ll mod) {
    return ((x % mod) * (y % mod)) % mod;
}

int main() {
    ll n;
    cin >> n;
    ll modulus = 1e9 + 7;
    vector<ll> seq(n + 1, -1);
    seq[0] = 2;
    seq[1] = 2;
    
    for (int i = 2; i < n; i++) {
        seq[i] = modAdd(seq[i - 1], seq[i - 2], modulus);
    }

    cout << seq[n - 1] << endl;
    return 0;
}
