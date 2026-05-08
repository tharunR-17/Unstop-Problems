#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> bfs(int src, int n, vector<vector<int>>& adj) {
    vector<int> dist(n, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int hub1, hub2, dest;
    cin >> hub1 >> hub2 >> dest;
    
    vector<int> d1 = bfs(hub1, n, adj);
    vector<int> d2 = bfs(hub2, n, adj);
    vector<int> dd = bfs(dest, n, adj);
    
    int ans = -1;
    for (int c = 0; c < n; c++) {
        if (d1[c] == -1 || d2[c] == -1 || dd[c] == -1) continue;
        int cost = d1[c] + d2[c] + dd[c];
        if (ans == -1 || cost < ans) ans = cost;
    }
    
    cout << ans << endl;
    return 0;
}
