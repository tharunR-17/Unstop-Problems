#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1), revGraph(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        revGraph[v].push_back(u);
    }

    vector<bool> visited(N + 1, false);
    stack<int> st;

    // First DFS: order by finishing time
    auto dfs1 = [&](auto &&self, int u) -> void {
        visited[u] = true;
        for (int v : graph[u]) {
            if (!visited[v])
                self(self, v);
        }
        st.push(u);
    };

    for (int i = 1; i <= N; i++) {
        if (!visited[i])
            dfs1(dfs1, i);
    }

    vector<int> comp(N + 1, -1);
    int sccCount = 0;

    // Second DFS on reversed graph
    auto dfs2 = [&](auto &&self, int u) -> void {
        comp[u] = sccCount;
        for (int v : revGraph[u]) {
            if (comp[v] == -1)
                self(self, v);
        }
    };

    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (comp[v] == -1) {
            dfs2(dfs2, v);
            sccCount++;
        }
    }

    vector<int> indegree(sccCount, 0);

    for (int u = 1; u <= N; u++) {
        for (int v : graph[u]) {
            if (comp[u] != comp[v]) {
                indegree[comp[v]]++;
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < sccCount; i++) {
        if (indegree[i] == 0)
            answer++;
    }

    cout << answer << "\n";

    return 0;
}
