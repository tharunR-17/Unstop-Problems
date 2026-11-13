#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

using ll = long long;

struct Batch {
    ll id, expiry, doses;
};

struct Event {
    char type;
    ll id, expiry, value;
};

struct Node {
    ll sum = 0;
    int active = 0;
    bool lazy = false;
};

class SegmentTree {
    vector<Node> tree;
    int n;

    void pull(int node) {
        tree[node].sum =
            tree[node * 2].sum + tree[node * 2 + 1].sum;

        tree[node].active =
            tree[node * 2].active + tree[node * 2 + 1].active;
    }

    void applyZero(int node) {
        tree[node].sum = 0;
        tree[node].active = 0;
        tree[node].lazy = true;
    }

    void push(int node) {
        if (tree[node].lazy) {
            applyZero(node * 2);
            applyZero(node * 2 + 1);
            tree[node].lazy = false;
        }
    }

    void build(int node, int l, int r, const vector<ll>& a) {
        if (l == r) {
            tree[node].sum = a[l];
            tree[node].active = (a[l] > 0);
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, a);
        build(node * 2 + 1, mid + 1, r, a);

        pull(node);
    }

    void updatePoint(int node, int l, int r,
                     int pos, ll val) {

        if (l == r) {
            tree[node].sum = val;
            tree[node].active = (val > 0);
            tree[node].lazy = false;
            return;
        }

        push(node);

        int mid = (l + r) / 2;

        if (pos <= mid) {
            updatePoint(node * 2, l, mid, pos, val);
        } else {
            updatePoint(node * 2 + 1, mid + 1, r, pos, val);
        }

        pull(node);
    }

    void clearRange(int node, int l, int r,
                    int ql, int qr) {

        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            applyZero(node);
            return;
        }

        push(node);

        int mid = (l + r) / 2;

        clearRange(node * 2, l, mid, ql, qr);
        clearRange(node * 2 + 1, mid + 1, r, ql, qr);

        pull(node);
    }

    int findBatch(int node, int l, int r,
                  ll &need, ll &used) {

        if (l == r) {
            used++;
            return l;
        }

        push(node);

        int mid = (l + r) / 2;
        int left = node * 2;

        if (tree[left].sum >= need) {
            return findBatch(
                left, l, mid, need, used
            );
        }

        need -= tree[left].sum;
        used += tree[left].active;

        return findBatch(
            left + 1, mid + 1, r, need, used
        );
    }

    ll getPoint(int node, int l, int r, int pos) {
        if (l == r)
            return tree[node].sum;

        push(node);

        int mid = (l + r) / 2;

        if (pos <= mid) {
            return getPoint(node * 2, l, mid, pos);
        }

        return getPoint(node * 2 + 1, mid + 1, r, pos);
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n + 5);
    }

    void build(const vector<ll>& a) {
        if (n > 0)
            build(1, 0, n - 1, a);
    }

    void setPoint(int pos, ll val) {
        updatePoint(1, 0, n - 1, pos, val);
    }

    void clearPrefix(int pos) {
        if (pos >= 0)
            clearRange(1, 0, n - 1, 0, pos);
    }

    ll totalDoses() {
        return tree[1].sum;
    }

    ll getPoint(int pos) {
        return getPoint(1, 0, n - 1, pos);
    }

    pair<int, ll> consume(ll x, ll &used) {
        ll need = x;

        int idx = findBatch(
            1, 0, n - 1, need, used
        );

        return {idx, need};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int B, Q;
    cin >> B >> Q;

    vector<Batch> initial(B);

    vector<pair<ll, ll>> keys;
    keys.reserve(B + Q);

    for (int i = 0; i < B; i++) {
        cin >> initial[i].id
            >> initial[i].expiry
            >> initial[i].doses;

        keys.push_back({
            initial[i].expiry,
            initial[i].id
        });
    }

    vector<Event> events(Q);

    for (int i = 0; i < Q; i++) {
        char type;
        cin >> type;

        events[i].type = type;

        if (type == 'A') {
            cin >> events[i].id
                >> events[i].expiry
                >> events[i].value;

            keys.push_back({
                events[i].expiry,
                events[i].id
            });
        }
        else if (type == 'R') {
            cin >> events[i].id;
        }
        else {
            cin >> events[i].value;
        }
    }

    // Coordinate compression.
    sort(keys.begin(), keys.end());

    int N = (int)keys.size();

    unordered_map<ll, int> position;
    position.reserve(N * 2 + 1);

    for (int i = 0; i < N; i++) {
        position[keys[i].second] = i;
    }

    if (N == 0) {
        for (const Event& ev : events) {
            if (ev.type == 'I')
                cout << "SHORT\n";
        }
        return 0;
    }

    // Initial doses.
    vector<ll> a(N, 0);

    for (const Batch& b : initial) {
        a[position[b.id]] = b.doses;
    }

    SegmentTree st(N);
    st.build(a);

    // Process events.
    for (const Event& ev : events) {

        if (ev.type == 'A') {

            int idx = position[ev.id];
            st.setPoint(idx, ev.value);

        }
        else if (ev.type == 'R') {

            int idx = position[ev.id];
            st.setPoint(idx, 0);

        }
        else {

            ll x = ev.value;

            // Check available stock.
            if (st.totalDoses() < x) {
                cout << "SHORT\n";
                continue;
            }

            ll used = 0;

            // Find last batch supplying doses.
            pair<int, ll> result = st.consume(x, used);

            int idx = result.first;
            ll taken = result.second;

            ll expiry = keys[idx].first;

            // Save remaining amount before clearing.
            ll oldAmount = st.getPoint(idx);

            // Remove all completely consumed batches.
            st.clearPrefix(idx - 1);

            // Update partially consumed final batch.
            st.setPoint(idx, oldAmount - taken);

            cout << expiry << " " << used << '\n';
        }
    }

    return 0;
}
