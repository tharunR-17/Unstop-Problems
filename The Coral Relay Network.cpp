#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;

    struct Edge {
        int to;
        ll w;
    };

    int n;
    ll D;

    vector<vector<Edge>> g;
    vector<int> sub;
    vector<bool> removed;

    // Find subtree sizes
    void calcSize(int u, int p) {
        sub[u] = 1;

        for (auto &e : g[u]) {
            int v = e.to;

            if (v == p || removed[v])
                continue;

            calcSize(v, u);
            sub[u] += sub[v];
        }
    }

    // Find centroid
    int getCentroid(int u, int p, int total) {
        for (auto &e : g[u]) {
            int v = e.to;

            if (v == p || removed[v])
                continue;

            if (sub[v] > total / 2)
                return getCentroid(v, u, total);
        }

        return u;
    }

    // Collect distances from centroid
    void collect(int u, int p, ll dist, vector<ll>& vals) {
        if (dist > D)
            return;

        vals.push_back(dist);

        for (auto &e : g[u]) {
            int v = e.to;

            if (v == p || removed[v])
                continue;

            collect(v, u, dist + e.w, vals);
        }
    }

    // Number of pairs whose sum <= D
    ll countPairs(vector<ll>& a) {
        sort(a.begin(), a.end());

        ll ans = 0;

        int l = 0;
        int r = (int)a.size() - 1;

        while (l < r) {
            if (a[l] + a[r] <= D) {
                // a[l] can pair with every element
                // from l+1 to r
                ans += r - l;
                l++;
            } else {
                r--;
            }
        }

        return ans;
    }

    ll solve(int entry) {
        // Find centroid of current component
        calcSize(entry, -1);

        int c = getCentroid(entry, -1, sub[entry]);

        removed[c] = true;

        /*
            All pairs whose path passes through c.

            Distance from c to itself = 0.
        */
        vector<ll> all;
        all.push_back(0);

        ll ans = 0;

        for (auto &e : g[c]) {
            int v = e.to;

            if (removed[v])
                continue;

            vector<ll> cur;

            collect(v, c, e.w, cur);

            // Pairs between this subtree and
            // previously collected nodes
            for (ll d : cur) {
                // Count how many distances in all
                // satisfy d + x <= D
                auto it = upper_bound(
                    all.begin(),
                    all.end(),
                    D - d
                );

                ans += it - all.begin();
            }

            // Add current subtree distances
            all.insert(all.end(), cur.begin(), cur.end());
        }

        /*
            Recursively solve each remaining component.
        */
        for (auto &e : g[c]) {
            int v = e.to;

            if (!removed[v]) {
                ans += solve(v);
            }
        }

        return ans;
    }

    long long countPairs(int N, long long d,
                         vector<vector<int>>& edges) {
        n = N;
        D = d;

        g.assign(n, {});
        sub.assign(n, 0);
        removed.assign(n, false);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            ll w = e[2];

            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        return solve(0);
    }
};
int main() {
    int n;
    long long D;

    cin >> n >> D;

    vector<vector<int>> edges(n - 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;

        cin >> u >> v >> w;

        // If sensors are numbered 1 to n
        --u;
        --v;

        edges[i] = {u, v, (int)w};
    }

    Solution s;

    cout << s.countPairs(n, D, edges);

    return 0;
}
