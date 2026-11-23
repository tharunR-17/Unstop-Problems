#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1e18;
const int INF_LOADS = 1e9;

struct State {
    long long waste;
    int loads;

    bool operator<(const State& other) const {
        if (waste != other.waste) return waste < other.waste;
        return loads < other.loads;
    }
};

struct Segment {
    long long val;
    int l;
    int r;
};

class LazySegTree {
    int n;
    vector<State> tree;
    vector<long long> lazy;

    void apply(int node, long long delta) {
        tree[node].waste += delta;
        lazy[node] += delta;
    }

    void push(int node) {
        if (lazy[node] != 0) {
            apply(node * 2, lazy[node]);
            apply(node * 2 + 1, lazy[node]);
            lazy[node] = 0;
        }
    }

    void point_set(int node, int start, int end, int idx, const State& val) {
        if (start == end) {
            tree[node] = val;
            lazy[node] = 0;
            return;
        }
        push(node);
        int mid = (start + end) >> 1;
        if (idx <= mid) {
            point_set(node * 2, start, mid, idx, val);
        } else {
            point_set(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    void range_add(int node, int start, int end, int l, int r, long long delta) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            apply(node, delta);
            return;
        }
        push(node);
        int mid = (start + end) >> 1;
        range_add(node * 2, start, mid, l, r, delta);
        range_add(node * 2 + 1, mid + 1, end, l, r, delta);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    State query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return {INF, INF_LOADS};
        if (l <= start && end <= r) return tree[node];
        push(node);
        int mid = (start + end) >> 1;
        return min(query(node * 2, start, mid, l, r),
                   query(node * 2 + 1, mid + 1, end, l, r));
    }

public:
    explicit LazySegTree(int size)
        : n(size), tree(4 * size, {INF, INF_LOADS}), lazy(4 * size, 0) {}

    void set_val(int idx, const State& val) {
        point_set(1, 0, n - 1, idx, val);
    }

    void add_range(int l, int r, long long delta) {
        if (l <= r && delta != 0) {
            range_add(1, 0, n - 1, l, r, delta);
        }
    }

    State query_min(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, A, B;
    if (!(cin >> n >> A >> B)) return 0;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<State> dp(n + 1, {INF, INF_LOADS});
    dp[0] = {0, 0};

    LazySegTree seg(n);
    vector<Segment> max_st, min_st;
    max_st.reserve(n);
    min_st.reserve(n);

    for (int i = 1; i <= n; ++i) {
        seg.set_val(i - 1, dp[i - 1]);

        int l_max = i - 1;
        while (!max_st.empty() && max_st.back().val <= a[i]) {
            Segment top = max_st.back();
            max_st.pop_back();
            seg.add_range(top.l, top.r, a[i] - top.val);
            l_max = top.l;
        }
        max_st.push_back({a[i], l_max, i - 1});

        int l_min = i - 1;
        while (!min_st.empty() && min_st.back().val >= a[i]) {
            Segment top = min_st.back();
            min_st.pop_back();
            seg.add_range(top.l, top.r, top.val - a[i]);
            l_min = top.l;
        }
        min_st.push_back({a[i], l_min, i - 1});

        if (i >= A) {
            int ql = max(0, i - B);
            int qr = i - A;
            State best = seg.query_min(ql, qr);
            if (best.waste < INF / 2) {
                dp[i] = {best.waste, best.loads + 1};
            }
        }
    }

    if (dp[n].waste >= INF / 2) {
        cout << "Cobalt plan: impossible\n";
    } else {
        cout << "Cobalt plan: waste " << dp[n].waste
             << " with " << dp[n].loads << " loads\n";
    }

    return 0;
}
