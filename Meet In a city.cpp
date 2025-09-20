#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;

vector<int> shortestPathFromNode(int source, const vector<vector<pii>>& adjList, int nodes) {
    vector<int> distance(nodes + 1, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> minHeap;
    
    distance[source] = 0;
    minHeap.push({0, source});
    
    while (!minHeap.empty()) {
        int current = minHeap.top().second;
        int cost = minHeap.top().first;
        minHeap.pop();
        
        if (cost > distance[current]) continue;
        
        for (const auto& edge : adjList[current]) {
            int neighbor = edge.first;
            int weight = edge.second;
            if (distance[neighbor] > distance[current] + weight) {
                distance[neighbor] = distance[current] + weight;
                minHeap.push({distance[neighbor], neighbor});
            }
        }
    }
    return distance;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<pii>> graph(N + 1);
    
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    
    vector<int> fromStart = shortestPathFromNode(1, graph, N);
    vector<int> fromEnd = shortestPathFromNode(N, graph, N);
    
    int smallestDiff = INT_MAX;
    for (int i = 1; i <= N; ++i) {
        if (fromStart[i] != INT_MAX && fromEnd[i] != INT_MAX) {
            smallestDiff = min(smallestDiff, abs(fromStart[i] - fromEnd[i]));
        }
    }
    
    cout << (smallestDiff == INT_MAX ? -1 : smallestDiff) << endl;
    
    return 0;
}
