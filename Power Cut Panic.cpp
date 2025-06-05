#include <bits/stdc++.h>
using namespace std;

int count_regions(int n, const vector<pair<int,int>>& connections) {
    vector<vector<int>> graph(n+1);
    for (auto& e : connections) {
        int u = e.first, v = e.second;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> visited(n+1, false);
    int regions = 0;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            // new region
            ++regions;
            queue<int> q;
            q.push(i);
            visited[i] = true;
            while (!q.empty()) {
                int node = q.front(); q.pop();
                for (int nei : graph[node]) {
                    if (!visited[nei]) {
                        visited[nei] = true;
                        q.push(nei);
                    }
                }
            }
        }
    }
    return regions;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> connections(m);
    for (int i = 0; i < m; ++i) {
        cin >> connections[i].first >> connections[i].second;
    }
    cout << count_regions(n, connections) << "\n";
    return 0;
}
