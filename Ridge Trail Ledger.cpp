#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

using ll = long long;

class SegmentTree {
private:
    struct Node {
        ll sumD = 0;
        ll sumA = 0;

        ll lazyD = 0;
        ll lazyC = 0;
        ll lazyA = 0;
    };

    int n;
    vector<Node> tree;

    void apply(int p, int l, int r, ll d, ll c, ll a) {
        ll oldD = tree[p].sumD;
        ll len = r - l + 1;

        tree[p].sumA += c * oldD + a * len;
        tree[p].sumD += d * len;

        // Correct lazy transformation composition
        tree[p].lazyA += a + c * tree[p].lazyD;
        tree[p].lazyC += c;
        tree[p].lazyD += d;
    }

    void push(int p, int l, int r) {
        if (l == r) return;

        ll d = tree[p].lazyD;
        ll c = tree[p].lazyC;
        ll a = tree[p].lazyA;

        if (d == 0 && c == 0 && a == 0) return;

        int mid = (l + r) / 2;

        apply(p * 2, l, mid, d, c, a);
        apply(p * 2 + 1, mid + 1, r, d, c, a);

        tree[p].lazyD = 0;
        tree[p].lazyC = 0;
        tree[p].lazyA = 0;
    }

    void update(int p, int l, int r,
                int ql, int qr, ll d, ll c, ll a) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            apply(p, l, r, d, c, a);
            return;
        }

        push(p, l, r);

        int mid = (l + r) / 2;

        update(p * 2, l, mid, ql, qr, d, c, a);
        update(p * 2 + 1, mid + 1, r, ql, qr, d, c, a);

        tree[p].sumD =
            tree[p * 2].sumD + tree[p * 2 + 1].sumD;

        tree[p].sumA =
            tree[p * 2].sumA + tree[p * 2 + 1].sumA;
    }

    ll query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr) {
            return tree[p].sumA;
        }

        push(p, l, r);

        int mid = (l + r) / 2;

        return query(p * 2, l, mid, ql, qr) +
               query(p * 2 + 1, mid + 1, r, ql, qr);
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n + 5);
    }

    // Increase current distinct counts by 1
    void addD(int l, int r) {
        if (l <= r) {
            update(1, 1, n, l, r, 1, 0, 0);
        }
    }

    // Add current distinct counts to historical totals
    void accumulate(int l, int r) {
        if (l <= r) {
            update(1, 1, n, l, r, 0, 1, 0);
        }
    }

    ll querySum(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

struct Event {
    int queryId;
    int left;
    int sign;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, q;
    cin >> m >> q;

    // Expand compressed runs
    vector<int> a;

    for (int i = 0; i < m; i++) {
        int code, len;
        cin >> code >> len;

        for (int j = 0; j < len; j++) {
            a.push_back(code);
        }
    }

    int n = (int)a.size();

    vector<vector<Event>> events(n + 1);
    vector<ll> answer(q, 0);

    // Convert each query into two offline events
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;

        events[r].push_back({i, l, 1});
        events[l - 1].push_back({i, l, -1});
    }

    SegmentTree seg(n);

    unordered_map<int, int> lastSeen;
    lastSeen.reserve(n * 2);

    // Process positions from left to right
    for (int r = 1; r <= n; r++) {
        int x = a[r - 1];

        int prev = 0;
        auto it = lastSeen.find(x);

        if (it != lastSeen.end()) {
            prev = it->second;
        }

        // New occurrence increases distinct count
        // for starting positions prev+1 to r
        seg.addD(prev + 1, r);

        // Accumulate current distinct counts
        seg.accumulate(1, r);

        lastSeen[x] = r;

        // Answer events at this right endpoint
        for (const Event &e : events[r]) {
            answer[e.queryId] +=
                e.sign * seg.querySum(e.left, n);
        }
    }

    // Events at time 0 have value zero.
    // Do not process them after the main loop.

    for (int i = 0; i < q; i++) {
        if (i > 0) cout << ' ';
        cout << answer[i];
    }

    cout << '\n';

    return 0;
}
