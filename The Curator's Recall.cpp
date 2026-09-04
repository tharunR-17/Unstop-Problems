#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to store each query
struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return r < other.r;
    }
};

int n, q;
vector<int> a;
vector<Query> queries;
vector<int> ans;
vector<int> bit;

// Fenwick Tree (Binary Indexed Tree) operations
void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx)
        bit[idx] += val;
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

int main() {
    // Optimize standard input/output streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    a.resize(n + 1);
    vector<int> vals;
    vals.reserve(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        vals.push_back(a[i]);
    }

    // Coordinate compression for large artist IDs
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
    }

    cin >> q;
    queries.resize(q);
    ans.resize(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    // Sort queries by their right endpoint (r)
    sort(queries.begin(), queries.end());

    bit.assign(n + 1, 0);
    vector<int> last_pos(vals.size() + 1, 0);

    int query_idx = 0;
    for (int i = 1; i <= n; ++i) {
        int artist = a[i];
        if (last_pos[artist] != 0) {
            update(last_pos[artist], -1);
        }
        update(i, 1);
        last_pos[artist] = i;

        // Answer all queries that end at the current position i
        while (query_idx < q && queries[query_idx].r == i) {
            ans[queries[query_idx].id] = query(queries[query_idx].r) - query(queries[query_idx].l - 1);
            query_idx++;
        }
    }

    // Print answers in the original order of queries
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}
