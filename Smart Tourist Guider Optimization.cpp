#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Edge {
    int to, weight;
};

// Dijkstra to find shortest TRAVEL time from all nodes to the destination
vector<int> get_shortest_paths(int start_node, int N, const vector<vector<Edge>>& adj) {
    vector<int> dist(N, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[start_node] = 0;
    pq.push({0, start_node});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& edge : adj[u]) {
            if (dist[u] + edge.weight < dist[edge.to]) {
                dist[edge.to] = dist[u] + edge.weight;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }
    return dist;
}

int solve() {
    int N, M, T;
    if (!(cin >> N >> M >> T)) return -1;

    vector<int> P(N), V(N);
    for (int i = 0; i < N; ++i) cin >> P[i] >> V[i];

    vector<vector<Edge>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].push_back({v - 1, w});
        adj[v - 1].push_back({u - 1, w});
    }

    // Precompute shortest travel times to spot N (index N-1)
    vector<int> distToN = get_shortest_paths(N - 1, N, adj);

    // dp[u][t] = max popularity at spot u at time t
    // Using a 1D vector of maps or a 2D array. 
    // Given T=10^5 and N=1000, we use a more memory-efficient 
    // approach: only store valid states.
    vector<vector<pair<int, int>>> dp(N); // dp[u] stores {time, popularity}

    // Check if start is even possible
    if (V[0] + distToN[0] + (N-1 == 0 ? 0 : 0) > T) {
        // Note: distToN[0] is travel, if N=1 it's 0. 
        // We must visit N, so time is V[0] + travel + V[N].
    }

    // Using a Priority Queue to process states in order of time
    // State: {time, node, popularity}
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

    if (V[0] <= T) {
        pq.push({V[0], {0, P[0]}});
    }

    int max_popularity = -1;
    // To prune: max_p[u] = max popularity reached at node u at ANY time <= current t
    vector<int> max_p_seen(N, -1);

    while (!pq.empty()) {
        int t = pq.top().first;
        int u = pq.top().second.first;
        int p = pq.top().second.second;
        pq.pop();

        // Pareto Pruning: If we've reached this node earlier with more popularity, skip
        if (p <= max_p_seen[u]) continue;
        max_p_seen[u] = p;

        // If we reached the destination, update answer
        if (u == N - 1) {
            max_popularity = max(max_popularity, p);
        }

        for (auto& edge : adj[u]) {
            int next_t = t + edge.weight + V[edge.to];
            int next_p = p + P[edge.to];

            // Tight Pruning: current time + travel to v + visit v + travel to N + visit N
            // If we are moving to v, and v is not N, we still need to reach N.
            int min_time_needed = next_t;
            if (edge.to != N - 1) {
                min_time_needed += distToN[edge.to] + V[N - 1];
            }

            if (min_time_needed <= T) {
                pq.push({next_t, {edge.to, next_p}});
            }
        }
    }

    return max_popularity;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << solve() << endl;
    return 0;
}
