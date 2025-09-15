#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define inf 1000000000000
typedef long long ll;
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

void computeBitwiseOperations() {
    ll x, y, z;
    cin >> x >> y >> z;
    ll andResult = x & y;
    ll orResult = x | y;
    ll xorResult = x ^ y;
    ll mask;

    if (z & 1) {
        mask = ((1 << (z % 5 + 2)) - 1);
    } else {
        mask = ((1 << (z % 10)) - 1);
    }

    cout << "AND: " << andResult << endl;
    cout << "OR: " << orResult << endl;
    cout << "XOR: " << xorResult << endl;
    cout << "Generated Bitmask: " << mask << endl;
    cout << "Masked AND: " << (mask & andResult) << endl;
    cout << "Masked OR: " << (mask & orResult) << endl;
    cout << "Masked XOR: " << (mask & xorResult) << endl;
}

int main() {
    fast;
    int t = 1;
    while (t--) {
        computeBitwiseOperations();
    }
    return 0;
}
