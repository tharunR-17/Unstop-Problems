#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 3000005; // Adjusted for larger constraints
int trie[MAX_NODES][2];
int counts[MAX_NODES];
int nodes_cnt = 1;

void insert(int num) {
    int curr = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (!trie[curr][bit]) {
            trie[curr][bit] = nodes_cnt++;
        }
        curr = trie[curr][bit];
        counts[curr]++; // Increment count at each node in the path
    }
}

long long countGreater(int x, int k) {
    int curr = 0;
    long long total = 0;
    for (int i = 30; i >= 0; i--) {
        if (curr == -1) break;
        int bitX = (x >> i) & 1;
        int bitK = (k >> i) & 1;

        if (bitK == 0) {
            // Path where XOR bit is 1 is definitely > K
            int high_branch = trie[curr][1 - bitX];
            if (high_branch) total += counts[high_branch];
            // Must keep checking path where XOR bit is 0
            curr = trie[curr][bitX] ? trie[curr][bitX] : -1;
        } else {
            // Path where XOR bit is 0 cannot be > K (it would be < K)
            // Must follow path where XOR bit is 1 to potentially be > K
            curr = trie[curr][1 - bitX] ? trie[curr][1 - bitX] : -1;
        }
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ans += countGreater(x, k);
        insert(x);
    }

    cout << ans << endl;
    return 0;
}
