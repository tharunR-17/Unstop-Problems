#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    long long val;
    int left, right;
};

vector<Node> tree;
long long peakCount = 0;

long long dfs(int u) {
    if (u == -1) return -1;

    long long leftMax = dfs(tree[u].left);
    long long rightMax = dfs(tree[u].right);

    long long descMax = max(leftMax, rightMax);

    // Leaf node
    if (tree[u].left == -1 && tree[u].right == -1) {
        peakCount++;
        return tree[u].val;
    }

    // Check if current node is greater than all descendants
    if (tree[u].val > descMax)
        peakCount++;

    return max(tree[u].val, descMax);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    tree.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> tree[i].val >> tree[i].left >> tree[i].right;
    }

    dfs(0);

    cout << peakCount << '\n';

    return 0;
}
