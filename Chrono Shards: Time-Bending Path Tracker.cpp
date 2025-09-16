#include <bits/stdc++.h>
using namespace std;

// The judge provides queryK in the real problem.
// Here it's just a placeholder.
int queryK(int edgeId) {
    return 1; // placeholder
}

struct Edge {
    int to;
    int baseCost;
    int type;   // 0 = Stable, 1 = Unstable
    int edgeId;
};

void chrono_shards(int n, int m, int start, int target, int maxEnergy, vector<vector<int>>& edges) {
    // Build adjacency list
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1], c = edges[i][2], t = edges[i][3];
        graph[u].push_back({v, c, t, i});
    }

    // Cache for k values of unstable edges
    vector<int> kCache(m, -1);

    // Priority queue holds (time, energy, node)
    using State = tuple<int,int,int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 0, start});

    // visited[node][energy] = minimum time used to reach
    vector<map<int,int>> visited(n + 1);

    while (!pq.empty()) {
        auto [time, energy, node] = pq.top();
        pq.pop();

        if (energy > maxEnergy) continue;
        if (node == target) {
            cout << time << "\n";
            return;
        }

        if (visited[node].count(energy) && visited[node][energy] <= time) 
            continue;
        visited[node][energy] = time;

        for (auto &e : graph[node]) {
            int cost = e.baseCost;
            if (e.type == 1) { // Unstable
                if (kCache[e.edgeId] == -1) {
                    kCache[e.edgeId] = queryK(e.edgeId);
                }
                cost += kCache[e.edgeId] * (time % 10);
            }

            int nextEnergy = energy + cost;
            if (nextEnergy <= maxEnergy) {
                pq.push({time + 1, nextEnergy, e.to});
            }
        }
    }

    cout << -1 << "\n"; // No valid path
}

int main() {
    int n, m, start, target, maxEnergy;
    cin >> n >> m >> start >> target >> maxEnergy;

    vector<vector<int>> edges(m, vector<int>(4));
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        string typeStr;
        cin >> u >> v >> cost >> typeStr;
        int type = (typeStr == "S") ? 0 : 1;
        edges[i][0] = u;
        edges[i][1] = v;
        edges[i][2] = cost;
        edges[i][3] = type;
    }

    chrono_shards(n, m, start, target, maxEnergy, edges);
    return 0;
}
