#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> role(n);
    for (int i = 0; i < n; i++) cin >> role[i];

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> parent(n, -1);
    vector<int> order;
    order.reserve(n);
    vector<bool> visited(n, false);

    queue<int> bfsQ;
    bfsQ.push(0);
    visited[0] = true;
    while (!bfsQ.empty()) {
        int node = bfsQ.front(); bfsQ.pop();
        order.push_back(node);
        for (int nb : adj[node]) {
            if (!visited[nb]) {
                visited[nb] = true;
                parent[nb] = node;
                bfsQ.push(nb);
            }
        }
    }

    vector<vector<int>> children(n);
    for (int i = 1; i < n; i++)
        children[parent[order[i]]].push_back(order[i]);


    vector<long long> dp1(n, 0), h0(n, 0);

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int v = order[i];

        if (children[v].empty()) {
            dp1[v] = role[v];
            h0[v]  = 1 - role[v];
            continue;
        }

        if (role[v] == 1) {
            long long prod = 1;
            for (int c : children[v])
                prod = prod * ((h0[c] + dp1[c]) % MOD) % MOD;
            dp1[v] = prod;
            h0[v]  = 0;
        } else {
            long long prod = 1;
            int zero_count = 0;
            for (int c : children[v]) {
                long long factor = (h0[c] + dp1[c]) % MOD;
                if (factor == 0) zero_count++;
                else prod = prod * factor % MOD;
            }

            h0[v] = (zero_count == 0) ? prod : 0;

            long long dp1_val = 0;

            if (zero_count == 0) {
                long long sum = 0;
                for (int c : children[v]) {
                    long long factor = (h0[c] + dp1[c]) % MOD;
                    sum = (sum + dp1[c] % MOD * modInverse(factor, MOD)) % MOD;
                }
                dp1_val = prod * sum % MOD;
            } else if (zero_count == 1) {
                for (int c : children[v]) {
                    long long factor = (h0[c] + dp1[c]) % MOD;
                    if (factor == 0) {
                        dp1_val = dp1[c] % MOD * prod % MOD;
                        break;
                    }
                }
            }

            dp1[v] = dp1_val;
        }
    }

    cout << dp1[0] << endl;
    return 0;
}
