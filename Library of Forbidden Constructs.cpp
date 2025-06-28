#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<int> in_degree;
vector<bool> visited, rec_stack;

bool has_cycle(int node) {
    visited[node] = true;
    rec_stack[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (has_cycle(neighbor)) return true;
        } else if (rec_stack[neighbor]) {
            return true;
        }
    }
    
    rec_stack[node] = false;
    return false;
}

vector<int> find_reading_order(int n, const vector<pair<int, int>>& edges) {
    // Initialize data structures
    graph.assign(n + 1, vector<int>());
    in_degree.assign(n + 1, 0);
    for (const auto& edge : edges) {
        int a = edge.first, b = edge.second;
        graph[a].push_back(b);
        in_degree[b]++;
    }
    
    // Check for cycles
    visited.assign(n + 1, false);
    rec_stack.assign(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (has_cycle(i)) {
                return {-1}; // Indicates IMPOSSIBLE
            }
        }
    }
    
    // Topological sort using priority queue
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            pq.push(i);
        }
    }
    
    vector<int> result;
    while (!pq.empty()) {
        int node = pq.top();
        pq.pop();
        result.push_back(node);
        
        // Process neighbors in sorted order
        vector<int> neighbors = graph[node];
        sort(neighbors.begin(), neighbors.end());
        for (int neighbor : neighbors) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                pq.push(neighbor);
            }
        }
    }
    
    // Check if all nodes are included
    if (result.size() != n) {
        return {-1}; // Indicates IMPOSSIBLE
    }
    
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }
    
    vector<int> result = find_reading_order(n, edges);
    if (result.size() == 1 && result[0] == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
