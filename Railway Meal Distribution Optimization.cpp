#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

string solve(int n, int m, vector<int>& c, vector<tuple<int, int, int>>& o) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<vector<pair<int, int>>> adj(n + 1);

    for (auto& x : o) {
        adj[get<0>(x)].push_back({get<1>(x), get<2>(x)});
    }

    for (int i = 1; i <= n; ++i) {
        for (auto& x : adj[i]) {
            pq.push(x);
        }

        while (!pq.empty() && pq.top().first <= i) {
            return "NO";
        }

        int cur = c[i - 1];

        while (cur > 0 && !pq.empty()) {
            pair<int, int> top = pq.top();
            pq.pop();

            int take = min(cur, top.second);
            cur -= take;
            top.second -= take;

            if (top.second > 0) {
                pq.push(top);
            }
        }
    }

    if (!pq.empty()) return "NO";
    return "YES";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i];

    vector<tuple<int, int, int>> o(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        o[i] = make_tuple(u, v, w);
    }

    cout << solve(n, m, c, o) << endl;

    return 0;
}
