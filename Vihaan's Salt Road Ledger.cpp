#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

struct Node {
    int left, right, cnt;
    ll sum;

    Node() : left(0), right(0), cnt(0), sum(0) {}
};

class PersistentSegmentTree {
private:
    vector<Node> tree;
    const vector<int>& values;

    int update(int prev, int l, int r, int pos, int val) {
        int cur = (int)tree.size();
        tree.push_back(tree[prev]);

        tree[cur].cnt++;
        tree[cur].sum += val;

        if (l == r) {
            return cur;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            int child = update(tree[prev].left, l, mid, pos, val);
            tree[cur].left = child;
        } else {
            int child = update(tree[prev].right, mid + 1, r, pos, val);
            tree[cur].right = child;
        }

        return cur;
    }

    ll largestSum(int a, int b, int k, int l, int r) const {
        int cnt = tree[a].cnt - tree[b].cnt;

        if (k <= 0 || cnt == 0) {
            return 0;
        }

        if (k >= cnt) {
            return tree[a].sum - tree[b].sum;
        }

        if (l == r) {
            return 1LL * k * values[l];
        }

        int mid = l + (r - l) / 2;

        int ar = tree[a].right;
        int br = tree[b].right;

        int rightCnt = tree[ar].cnt - tree[br].cnt;

        if (k <= rightCnt) {
            return largestSum(ar, br, k, mid + 1, r);
        }

        ll rightSum = tree[ar].sum - tree[br].sum;

        return rightSum +
               largestSum(tree[a].left, tree[b].left,
                          k - rightCnt, l, mid);
    }

public:
    PersistentSegmentTree(const vector<int>& compressedValues, int n)
        : values(compressedValues) {
        tree.reserve((size_t)n * 20 + 1);
        tree.push_back(Node());
    }

    int add(int previousRoot, int m, int pos, int val) {
        return update(previousRoot, 0, m - 1, pos, val);
    }

    ll getLargestSum(int rootA, int rootB, int k, int m) const {
        return largestSum(rootA, rootB, k, 0, m - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> levy(n + 1);
    vector<int> values;
    values.reserve(n);

    for (int i = 1; i <= n; i++) {
        cin >> levy[i];
        values.push_back(levy[i]);
    }

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    int m = (int)values.size();

    vector<int> compressed(n + 1);

    for (int i = 1; i <= n; i++) {
        compressed[i] = lower_bound(
            values.begin(), values.end(), levy[i]
        ) - values.begin();
    }

    int LOG = 1;
    while ((1 << LOG) <= n) {
        LOG++;
    }

    vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.reserve(n);

    // Iterative traversal, rooted at town 1.
    order.push_back(1);

    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];

        for (int to : adj[v]) {
            if (to == parent[v]) {
                continue;
            }

            parent[to] = v;
            order.push_back(to);
        }
    }

    for (int v = 1; v <= n; v++) {
        up[0][v] = parent[v];
    }

    for (int j = 1; j < LOG; j++) {
        for (int v = 1; v <= n; v++) {
            up[j][v] = up[j - 1][up[j - 1][v]];
        }
    }

    PersistentSegmentTree pst(values, n);

    vector<int> version(n + 1, 0);
    vector<ll> prefixSum(n + 1, 0);

    // Each version stores levy frequencies on the root-to-node path.
    for (int v : order) {
        int p = parent[v];

        prefixSum[v] = prefixSum[p] + levy[v];

        version[v] = pst.add(
            version[p], m, compressed[v], levy[v]
        );
    }

    while (q--) {
        int u, k;
        ll budget;
        cin >> u >> budget >> k;

        int current = u;

        // Jump toward the capital whenever the candidate is affordable.
        for (int j = LOG - 1; j >= 0; j--) {
            int candidate = up[j][current];

            if (candidate == 0) {
                continue;
            }

            int rootA = version[parent[u]];
            int rootB = version[parent[candidate]];

            ll total = prefixSum[parent[u]]
                     - prefixSum[parent[candidate]];

            ll waived = pst.getLargestSum(rootA, rootB, k, m);
            ll cost = total - waived;

            if (cost <= budget) {
                current = candidate;
            }
        }

        int destination = current;

        int rootA = version[parent[u]];
        int rootB = version[parent[destination]];

        ll total = prefixSum[parent[u]]
                 - prefixSum[parent[destination]];

        ll waived = pst.getLargestSum(rootA, rootB, k, m);
        ll cost = total - waived;

        cout << destination << ' ' << cost << '\n';
    }

    return 0;
}
