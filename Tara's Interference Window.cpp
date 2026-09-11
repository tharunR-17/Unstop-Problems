#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    int child[2];
    int cnt;

    TrieNode() {
        child[0] = child[1] = -1;
        cnt = 0;
    }
};

class BinaryTrie {
    vector<TrieNode> trie;

public:
    BinaryTrie() {
        trie.emplace_back();
    }

    void insert(int x) {
        int node = 0;
        trie[node].cnt++;

        for (int bit = 30; bit >= 0; bit--) {
            int b = (x >> bit) & 1;

            if (trie[node].child[b] == -1) {
                trie[node].child[b] = trie.size();
                trie.emplace_back();
            }

            node = trie[node].child[b];
            trie[node].cnt++;
        }
    }

    void erase(int x) {
        int node = 0;
        trie[node].cnt--;

        for (int bit = 30; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            node = trie[node].child[b];
            trie[node].cnt--;
        }
    }

    int maxXor(int x) {
        int node = 0;
        int ans = 0;

        for (int bit = 30; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            int opposite = b ^ 1;

            if (trie[node].child[opposite] != -1 &&
                trie[trie[node].child[opposite]].cnt > 0) {

                ans |= (1 << bit);
                node = trie[node].child[opposite];
            }
            else {
                node = trie[node].child[b];
            }
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, K;
    cin >> n >> K;

    vector<int> w(n + 1);
    vector<int> prefix(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        prefix[i] = prefix[i - 1] ^ w[i];
    }

    BinaryTrie trie;

    int answer = 0;

    for (int r = 1; r <= n; r++) {

        // P[r-1] gives subarrays ending at r.
        // Their lengths can be from 1 to K.
        trie.insert(prefix[r - 1]);

        // Remove prefix values that would give length > K.
        if (r - K - 1 >= 0) {
            trie.erase(prefix[r - K - 1]);
        }

        answer = max(answer, trie.maxXor(prefix[r]));
    }

    cout << answer << '\n';

    return 0;
}
