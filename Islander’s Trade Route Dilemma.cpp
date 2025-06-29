#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Edge = pair<int, int>; // (v, t)
using State = tuple<int, int, int, vector<int>>; // (u, mask, totalTime, collectionTimes)

bool can_reach_with_freshness(int n, int k, const vector<int>& goods, const vector<vector<Edge>>& adj, ll x) {
    queue<State> q;
    unordered_map<ll, ll> seen; // (u, mask) -> min time

    vector<int> initial_times = {0};
    q.emplace(1, 1 << goods[0], 0, initial_times);
    seen[1LL + ((ll)(1 << goods[0]) << 32)] = 0;

    while (!q.empty()) {
        auto [u, mask, total_time, collection_times] = q.front();
        q.pop();

        if (u == n) {
            vector<int> fresh_goods;
            for (int i = 0; i < collection_times.size(); i++) {
                if (total_time - collection_times[i] <= x) {
                    fresh_goods.push_back(i);
                }
            }
            if (fresh_goods.size() >= k) {
                return true;
            }
        }

        for (const auto& [v, t] : adj[u]) {
            ll new_time = total_time + t;
            int new_mask = mask;
            vector<int> new_collection_times = collection_times;

            int good_v = goods[v - 1];
            if (!(mask & (1 << good_v))) {
                new_mask |= 1 << good_v;
                new_collection_times.push_back(new_time);
            }

            ll state_key = v + ((ll)new_mask << 32);
            if (seen.find(state_key) == seen.end() || seen[state_key] > new_time) {
                seen[state_key] = new_time;
                q.emplace(v, new_mask, new_time, new_collection_times);
            }
        }
    }
    return false;
}

ll solve(int n, int m, int k, const vector<int>& goods, const vector<vector<Edge>>& adj) {
    ll left = 0, right = 1e9;
    ll result = -1;

    while (left <= right) {
        ll mid = (left + right) / 2;
        if (can_reach_with_freshness(n, k, goods, adj, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> goods(n);
    for (int i = 0; i < n; i++) {
        cin >> goods[i];
    }

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        adj[u].emplace_back(v, t);
    }

    cout << solve(n, m, k, goods, adj) << '\n';
    return 0;
}
