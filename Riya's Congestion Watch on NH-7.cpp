#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 2e18;

struct SegmentTree {
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    SegmentTree(int n) : n(n) {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node * 2] += lazy[node];
            lazy[node * 2] += lazy[node];
            tree[node * 2 + 1] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
            lazy[node] = 0;
        }
    }

    void build(const vector<long long>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, node * 2, start, mid);
        build(arr, node * 2 + 1, mid + 1, end);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int start, int end, int l, int r, long long val) {
        if (l > end || r < start)
            return;
        if (l <= start && end <= r) {
            tree[node] += val;
            lazy[node] += val;
            return;
        }
        push(node, start, end);
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, val);
        update(node * 2 + 1, mid + 1, end, l, r, val);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    long long queryMax(int node, int start, int end, int l, int r) {
        if (l > end || r < start)
            return -INF;
        if (l <= start && end <= r)
            return tree[node];
        push(node, start, end);
        int mid = (start + end) / 2;
        return max(queryMax(node * 2, start, mid, l, r),
                   queryMax(node * 2 + 1, mid + 1, end, l, r));
    }

    int queryFirstGreater(int node, int start, int end, int l, int r, long long x) {
        if (l > end || r < start || tree[node] <= x)
            return -1;
        if (start == end)
            return start;
        
        push(node, start, end);
        int mid = (start + end) / 2;
        
        int res = queryFirstGreater(node * 2, start, mid, l, r, x);
        if (res != -1) return res;
        
        return queryFirstGreater(node * 2 + 1, mid + 1, end, l, r, x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    SegmentTree st(n);
    st.build(arr, 1, 1, n);

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            st.update(1, 1, n, l, r, v);
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            cout << st.queryMax(1, 1, n, l, r) << "\n";
        } else if (type == 3) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            cout << st.queryFirstGreater(1, 1, n, l, r, x) << "\n";
        }
    }

    return 0;
}
