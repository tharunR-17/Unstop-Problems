#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_len = 1;

void dfs(int node, long long sum, int visited, const vector<int>& values,
         const vector<vector<int>>& graph, int length) {
    max_len = max(max_len, length);

    for (int neighbor : graph[node]) {
        if (!(visited & (1 << neighbor))) {
            if (sum % values[neighbor] == 0) {
                dfs(neighbor, sum + values[neighbor], visited | (1 << neighbor), values, graph, length + 1);
            }
        }
    }
}

int getLongestChain(int n, int m, const vector<int>& values, const vector<pair<int, int>>& edge_list) {
    vector<vector<int>> graph(n);

    for (int i = 0; i < m; ++i) {
        int u = edge_list[i].first - 1; // convert to 0-based
        int v = edge_list[i].second - 1;
        graph[u].push_back(v);
    }

    max_len = 1;

    for (int i = 0; i < n; ++i) {
        int visited = (1 << i);
        dfs(i, values[i], visited, values, graph, 1);
    }

    return max_len;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> values(n);
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    vector<pair<int, int>> edge_list(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edge_list[i] = make_pair(u, v);
    }

    int result = getLongestChain(n, m, values, edge_list);
    cout << result << endl;

    return 0;
}
