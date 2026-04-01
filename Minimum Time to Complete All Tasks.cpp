#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int minimumTime(int N, vector<int>& time, int M, vector<pair<int, int>>& dependencies) {
    vector<vector<int>> adj(N); // Adjacency list for the graph
    vector<int> inDegree(N, 0); // In-degree of each node
    vector<int> finishTime(N, 0); // Finish time of each task

    // Build the graph and in-degree array
    for (auto& dep : dependencies) {
        adj[dep.first].push_back(dep.second);
        inDegree[dep.second]++;
    }

    queue<int> q;
    
    // Initialize tasks with no dependencies
    for (int i = 0; i < N; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
            finishTime[i] = time[i]; // Task with no dependencies finishes at its own time
        }
    }

    // Process tasks using BFS (Topological Sort)
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adj[current]) {
            inDegree[neighbor]--;
            finishTime[neighbor] = max(finishTime[neighbor], finishTime[current] + time[neighbor]);
            
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // Find the maximum finish time among all tasks
    return *max_element(finishTime.begin(), finishTime.end());
}

int main() {
    int N, M;
    cin >> N;
    vector<int> time(N);

    for (int i = 0; i < N; ++i) {
        cin >> time[i];
    }

    cin >> M;
    vector<pair<int, int>> dependencies(M);
    for (int i = 0; i < M; ++i) {
        cin >> dependencies[i].first >> dependencies[i].second;
    }

    cout << minimumTime(N, time, M, dependencies) << endl;

    return 0;
}
