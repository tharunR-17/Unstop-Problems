#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

struct Node {
    int len;
    int first_val, last_val;
    int max_inc, pref_inc, suff_inc;
    int max_dec, pref_dec, suff_dec;
};

Node merge_nodes(const Node& L, const Node& R) {
    if (L.len == 0) return R;
    if (R.len == 0) return L;

    Node res;
    res.len = L.len + R.len;
    res.first_val = L.first_val;
    res.last_val = R.last_val;

    // Strictly Increasing (Left to Right)
    res.max_inc = max(L.max_inc, R.max_inc);
    res.pref_inc = L.pref_inc;
    if (L.pref_inc == L.len && L.last_val < R.first_val) {
        res.pref_inc += R.pref_inc;
    }
    res.suff_inc = R.suff_inc;
    if (R.suff_inc == R.len && L.last_val < R.first_val) {
        res.suff_inc += L.suff_inc;
    }
    if (L.last_val < R.first_val) {
        res.max_inc = max(res.max_inc, L.suff_inc + R.pref_inc);
    }

    // Strictly Decreasing (Left to Right) -> Increasing (Right to Left)
    res.max_dec = max(L.max_dec, R.max_dec);
    res.pref_dec = L.pref_dec;
    if (L.pref_dec == L.len && L.last_val > R.first_val) {
        res.pref_dec += R.pref_dec;
    }
    res.suff_dec = R.suff_dec;
    if (R.suff_dec == R.len && L.last_val > R.first_val) {
        res.suff_dec += L.suff_dec;
    }
    if (L.last_val > R.first_val) {
        res.max_dec = max(res.max_dec, L.suff_dec + R.pref_dec);
    }

    return res;
}

Node reverse_node(const Node& node) {
    Node res = node;
    swap(res.first_val, res.last_val);
    swap(res.max_inc, res.max_dec);
    swap(res.pref_inc, res.suff_dec);
    swap(res.suff_inc, res.pref_dec);
    return res;
}

int N, Q;
vector<int> adj[MAXN];
int initial_strength[MAXN];

// HLD variables
int parent_node[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
int cur_pos;

// Segment Tree
Node tree[4 * MAXN];

int dfs_hld(int v, int p, int d) {
    parent_node[v] = p;
    depth[v] = d;
    int size = 1;
    int max_c_size = 0;
    heavy[v] = -1;
    for (int c : adj[v]) {
        if (c != p) {
            int c_size = dfs_hld(c, v, d + 1);
            size += c_size;
            if (c_size > max_c_size) {
                max_c_size = c_size;
                heavy[v] = c;
            }
        }
    }
    return size;
}

void decompose(int v, int h) {
    head[v] = h;
    pos[v] = ++cur_pos;
    if (heavy[v] != -1) {
        decompose(heavy[v], h);
    }
    for (int c : adj[v]) {
        if (c != parent_node[v] && c != heavy[v]) {
            decompose(c, c);
        }
    }
}

Node make_leaf(int val) {
    return {1, val, val, 1, 1, 1, 1, 1, 1};
}

void update_tree(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = make_leaf(val);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update_tree(2 * node, start, mid, idx, val);
    else update_tree(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = merge_nodes(tree[2 * node], tree[2 * node + 1]);
}

Node query_tree(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return {0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return merge_nodes(query_tree(2 * node, start, mid, l, r),
                       query_tree(2 * node + 1, mid + 1, end, l, r));
}

int query_path(int a, int b) {
    vector<Node> left_list, right_list;

    while (head[a] != head[b]) {
        if (depth[head[a]] > depth[head[b]]) {
            Node res = query_tree(1, 1, N, pos[head[a]], pos[a]);
            left_list.push_back(reverse_node(res));
            a = parent_node[head[a]];
        } else {
            Node res = query_tree(1, 1, N, pos[head[b]], pos[b]);
            right_list.push_back(res);
            b = parent_node[head[b]];
        }
    }

    if (depth[a] > depth[b]) {
        Node res = query_tree(1, 1, N, pos[b], pos[a]);
        left_list.push_back(reverse_node(res));
    } else {
        Node res = query_tree(1, 1, N, pos[a], pos[b]);
        right_list.push_back(res);
    }

    // Combine left parts (from a to LCA)
    Node final_res = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (const auto& node : left_list) {
        final_res = merge_nodes(final_res, node);
    }
    // Combine right parts (from LCA down to b, in reverse order of discovery)
    for (int i = (int)right_list.size() - 1; i >= 0; --i) {
        final_res = merge_nodes(final_res, right_list[i]);
    }

    return final_res.max_inc;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N >> Q)) return 0;

    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; ++i) {
        cin >> initial_strength[i];
    }

    dfs_hld(1, 0, 0);
    decompose(1, 1);

    for (int i = 1; i <= N; ++i) {
        update_tree(1, 1, N, pos[i], initial_strength[i]);
    }

    for (int i = 0; i < Q; ++i) {
        char type;
        cin >> type;
        if (type == 'U') {
            int v, x;
            cin >> v >> x;
            update_tree(1, 1, N, pos[v], x);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query_path(a, b) << "\n";
        }
    }

    return 0;
}
