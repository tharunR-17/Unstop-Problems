#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // LOG is enough for n <= 2 * 10^5
    int LOG = 20;

    while ((1 << LOG) <= n)
        LOG++;

    vector<vector<int>> up(LOG, vector<int>(n, -1));

    // mx[k][v] = maximum strength among the first 2^k
    // ancestors of v (excluding v itself).
    vector<vector<int>> mx(LOG, vector<int>(n, INT_MIN));

    vector<int> depth(n, 0);
    vector<int> parent(n, -1);

    // Build parent/depth iteratively.
    vector<int> order;
    order.reserve(n);

    vector<int> st;
    st.push_back(0);
    parent[0] = -1;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        order.push_back(u);

        for (int v : adj[u]) {
            if (v == parent[u])
                continue;

            parent[v] = u;
            depth[v] = depth[u] + 1;
            st.push_back(v);
        }
    }

    // k = 0: immediate parent
    for (int v = 0; v < n; v++) {
        if (parent[v] != -1) {
            up[0][v] = parent[v];
            mx[0][v] = a[parent[v]];
        }
    }

    // Binary lifting tables.
    for (int k = 1; k < LOG; k++) {
        for (int v = 0; v < n; v++) {
            int mid = up[k - 1][v];

            if (mid != -1) {
                up[k][v] = up[k - 1][mid];

                mx[k][v] = max(
                    mx[k - 1][v],
                    mx[k - 1][mid]
                );
            }
        }
    }

    vector<int> ans(n, -1);

    for (int v = 1; v < n; v++) {
        int cur = v;

        /*
            Move upward as long as the whole block of ancestors
            contains no node with strength > a[v].

            After this process:
              parent[cur] = nearest ancestor with strength > a[v]
        */
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][cur] != -1 && mx[k][cur] <= a[v]) {
                cur = up[k][cur];
            }
        }

        if (parent[cur] != -1 && a[parent[cur]] > a[v]) {
            ans[v] = parent[cur] + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i)
            cout << ' ';

        cout << ans[i];
    }

    cout << '\n';

    return 0;
}
