#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<vector<pair<int,int>>> road(n), rail(n);
    
    int r;
    cin >> r;
    while (r--) {
        int u, v, t;
        cin >> u >> v >> t;
        road[u].push_back({v, t});
        road[v].push_back({u, t});
    }
    
    int s;
    cin >> s;
    while (s--) {
        int u, v, t;
        cin >> u >> v >> t;
        rail[u].push_back({v, t});
        rail[v].push_back({u, t});
    }
    
    int m;
    cin >> m;
    vector<bool> isIntermodal(n, false);
    for (int i = 0; i < m; i++) {
        int h;
        cin >> h;
        isIntermodal[h] = true;
    }
    
    int transferTime, src, dst;
    cin >> transferTime >> src >> dst;
    
    if (src == dst) {
        cout << 0 << endl;
        return 0;
    }
    
    const long long INF = 1e18;
    vector<vector<long long>> dist(n, vector<long long>(2, INF));
    
    priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>, greater<>> pq;
    
    dist[src][0] = 0;
    dist[src][1] = 0;
    pq.push({0, src, 0});
    pq.push({0, src, 1});
    
    while (!pq.empty()) {
        auto [d, u, mode] = pq.top();
        pq.pop();
        
        if (d > dist[u][mode]) continue;
        
        auto& routes = (mode == 0) ? road[u] : rail[u];
        for (auto [v, t] : routes) {
            long long nd = d + t;
            if (nd < dist[v][mode]) {
                dist[v][mode] = nd;
                pq.push({nd, v, mode});
            }
        }
        
        if (isIntermodal[u]) {
            int other = 1 - mode;
            long long nd = d + transferTime;
            if (nd < dist[u][other]) {
                dist[u][other] = nd;
                pq.push({nd, u, other});
            }
        }
    }
    
    long long ans = min(dist[dst][0], dist[dst][1]);
    cout << (ans == INF ? -1 : ans) << endl;
    
    return 0;
}
