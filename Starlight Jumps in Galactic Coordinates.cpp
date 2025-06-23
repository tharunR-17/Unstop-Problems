#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

struct State {
    int cost, node, config;
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

int starlightJumps(int N, int M, int K, vector<int>& bits, vector<tuple<int, int, int, int, int>>& edges) {
    int startConfig = 0;
    for (int b : bits) startConfig |= (1 << b);

    vector<vector<tuple<int, int, int, int>>> graph(N + 1);
    for (auto& [u, v, cost, bm, flip] : edges) {
        graph[u].emplace_back(v, cost, bm, flip);
    }

    vector<vector<int>> visited(N + 1, vector<int>(1024, INT_MAX));
    visited[1][startConfig] = 0;

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, 1, startConfig});

    while (!pq.empty()) {
        auto [cost, node, config] = pq.top();
        pq.pop();

        if (node == N && config == startConfig) return cost;
        if (visited[node][config] < cost) continue;

        for (auto& [nei, c, bm, flip] : graph[node]) {
            if ((config & bm) == bm) {
                int newConfig = config ^ flip;
                int newCost = cost + c;
                if (visited[nei][newConfig] > newCost) {
                    visited[nei][newConfig] = newCost;
                    pq.push({newCost, nei, newConfig});
                }
            }
        }
    }

    return -1;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> bits(K);
    for (int i = 0; i < K; ++i) cin >> bits[i];

    vector<tuple<int, int, int, int, int>> edges(M);
    for (int i = 0; i < M; ++i) {
        int u, v, cost, bm, flip;
        cin >> u >> v >> cost >> bm >> flip;
        edges[i] = {u, v, cost, bm, flip};
    }

    cout << starlightJumps(N, M, K, bits, edges) << endl;
    return 0;
}
