#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int destination, activationTime, duration;
    Edge(int dest, int act, int dur) : destination(dest), activationTime(act), duration(dur) {}
};

int findMinTime(int N, int M, vector<vector<Edge>> &adjList) {
    vector<int> minTime(N + 1, INT_MAX);
    minTime[1] = 0; // Start from island 1

    // Min-heap based on time
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1}); // {time, island}

    while (!pq.empty()) {
        int currentTime = pq.top().first;
        int island = pq.top().second;
        pq.pop();

        if (currentTime > minTime[island]) continue;

        for (Edge edge : adjList[island]) {
            int nextIsland = edge.destination;
            int timeToCross = max(currentTime, edge.activationTime) + edge.duration;

            if (timeToCross < minTime[nextIsland]) {
                minTime[nextIsland] = timeToCross;
                pq.push({timeToCross, nextIsland});
            }
        }
    }

    return minTime[N] == INT_MAX ? -1 : minTime[N];
}

int main() {
    int N, M, K;
    cin >> N >> M >> K; // K is unused but read to match format

    vector<vector<Edge>> adjList(N + 1);

    for (int i = 0; i < M; i++) {
        int u, v, t, d;
        cin >> u >> v >> t >> d;
        adjList[u].push_back(Edge(v, t, d));
        adjList[v].push_back(Edge(u, t, d)); // undirected
    }

    int result = findMinTime(N, M, adjList);
    cout << result << endl;

    return 0;
}
