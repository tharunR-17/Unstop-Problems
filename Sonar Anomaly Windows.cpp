#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int BITS = 20;

// Each insertion creates 21 nodes:
// 1 root + 20 bit-nodes
const int MAXNODE = (MAXN + 5) * 21;

struct Node {
    int child[2];
    int cnt;
};

Node trie[MAXNODE];
int root[MAXN + 5];
int nodes = 0;

// Clone old node and return new node index
int cloneNode(int oldNode) {
    ++nodes;

    trie[nodes] = trie[oldNode];

    return nodes;
}

int insertNumber(int previousRoot, int value) {

    int newRoot = cloneNode(previousRoot);

    int prev = previousRoot;
    int curr = newRoot;

    trie[curr].cnt++;

    for (int bit = 19; bit >= 0; bit--) {

        int b = (value >> bit) & 1;

        int oldChild = trie[prev].child[b];

        int newChild = cloneNode(oldChild);

        trie[curr].child[b] = newChild;

        prev = oldChild;
        curr = newChild;

        trie[curr].cnt++;
    }

    return newRoot;
}

int getMaxXor(int leftRoot, int rightRoot, int x) {

    int leftNode = leftRoot;
    int rightNode = rightRoot;

    int ans = 0;

    for (int bit = 19; bit >= 0; bit--) {

        int xBit = (x >> bit) & 1;

        // To maximize XOR, try opposite bit
        int wanted = xBit ^ 1;

        int rightWanted =
            trie[rightNode].child[wanted];

        int leftWanted =
            trie[leftNode].child[wanted];

        // How many numbers from [l, r]
        // are present in wanted branch?
        int count =
            trie[rightWanted].cnt -
            trie[leftWanted].cnt;

        if (count > 0) {

            // XOR bit becomes 1
            ans |= (1 << bit);

            rightNode = rightWanted;
            leftNode = leftWanted;
        }
        else {

            // Opposite bit unavailable,
            // so take same bit.
            int same = xBit;

            rightNode =
                trie[rightNode].child[same];

            leftNode =
                trie[leftNode].child[same];
        }
    }

    return ans;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    root[0] = 0;

    for (int i = 1; i <= n; i++) {

        int value;
        cin >> value;

        root[i] =
            insertNumber(root[i - 1], value);
    }

    int q;
    cin >> q;

    while (q--) {

        int l, r, x;

        cin >> l >> r >> x;

        cout << getMaxXor(
            root[l - 1],
            root[r],
            x
        ) << '\n';
    }

    return 0;
}
