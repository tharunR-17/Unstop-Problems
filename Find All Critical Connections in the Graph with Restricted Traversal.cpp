#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int timer = 1;

void dfs(int node, int parent, vector<int> adj[], vector<int> &disc, vector<int> &low,
         vector<vector<int>> &bridges, vector<int> &visits) {
    visits[node]++;
    if (visits[node] > 2) return; // Constraint: visit at most twice

    disc[node] = low[node] = timer++;

    for (int neigh : adj[node]) {
        if (neigh == parent) continue;

        if (disc[neigh] == -1) {
            dfs(neigh, node, adj, disc, low, bridges, visits);
            low[node] = min(low[node], low[neigh]);

            // Bridge condition
            if (low[neigh] > disc[node]) {
                bridges.push_back({min(node, neigh), max(node, neigh)});
            }
        } else {
            low[node] = min(low[node], disc[neigh]);
        }
    }
}

void find_critical_connections(int v, vector<vector<int>> &edges) {
    /* Write your logic here */
    vector<int> adj[v];
    for (auto &e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    vector<int> disc(v, -1), low(v, -1), visits(v, 0);
    vector<vector<int>> bridges;

    for (int i = 0; i < v; i++) {
        if (disc[i] == -1) {
            dfs(i, -1, adj, disc, low, bridges, visits);
        }
    }

    sort(bridges.begin(), bridges.end());
    for (auto &b : bridges) {
        cout << b[0] << " " << b[1] << "\n";
    }

}

int main() {
    int v, e;
    cin >> v >> e;
    vector<vector<int>> edges(e, vector<int>(2));
    for (int i = 0; i < e; ++i) {
        cin >> edges[i][0] >> edges[i][1];
    }
    find_critical_connections(v, edges);
    /* Print the output */
    return 0;
}
