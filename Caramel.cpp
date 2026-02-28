#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;
const int MAXN = 100010;

// Function for modular exponentiation
long long qp(long long x, long long y) {
    long long z = 1;
    while (y > 0) {
        if (y & 1) {
            z = z * x % MOD;
        }
        x = x * x % MOD;
        y >>= 1;
    }
    return z;
}

int main() {
    int n, K;
    cin >> n >> K;

    vector<vector<long long>> f(2, vector<long long>(MAXN, 0));
    int cur = 0, nxt = 1;
    f[cur][0] = 1;

    for (int i = 1; i <= 2 * n; i++) {
        f[nxt][0] = 0;
        for (int j = 1; j <= K; j++) {
            f[nxt][j] = f[cur][j - 1];
        }
        for (int j = 1; j <= K; j++) {
            f[nxt][j - 1] = (f[nxt][j - 1] + j * f[cur][j] % MOD) % MOD;
        }
        swap(cur, nxt);
    }

    long long all = 1;
    for (int i = 1; i <= 2 * n; i += 2) {
        all = all * i % MOD;
    }

    long long result = f[cur][0] * qp(all, MOD - 2) % MOD;
    cout << result << endl;

    return 0;
}
