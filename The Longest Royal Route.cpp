#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;


int main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(1);
    dist[1] = 0;

    int maxDist = 0;
    while (!q.empty()) {
        int city = q.front(); q.pop();
        for (int neighbor : adj[city]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[city] + 1;
                maxDist = max(maxDist, dist[neighbor]);
                q.push(neighbor);
            }
        }
    }

    cout << maxDist << endl;
    return 0;
}
