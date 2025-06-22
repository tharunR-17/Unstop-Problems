#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m; // number of modules and dependencies

    vector<int> chronoLock(n + 1); // 1-based indexing
    for (int i = 1; i <= n; i++) {
        cin >> chronoLock[i];
    }

    vector<vector<int>> graph(n + 1);
    vector<vector<int>> revGraph(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        revGraph[v].push_back(u);
        indegree[v]++;
    }

    // Topological Sort (Kahn's algorithm)
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> topoOrder;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);
        for (int neighbor : graph[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (topoOrder.size() != n) {
        cout << "CYCLE DETECTED" << endl;
        return 0;
    }

    vector<int> upgradeTime(n + 1, 0);
    for (int node : topoOrder) {
        int maxDepTime = 0;
        for (int pre : revGraph[node]) {
            maxDepTime = max(maxDepTime, upgradeTime[pre]);
        }
        upgradeTime[node] = max(maxDepTime + 1, chronoLock[node]);
    }

    int maxTime = 0;
    for (int i = 1; i <= n; i++) {
        maxTime = max(maxTime, upgradeTime[i]);
    }

    cout << maxTime << endl;

    return 0;
}
