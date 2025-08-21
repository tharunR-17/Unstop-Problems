#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct State {
    int node;
    int time;
    bool operator>(const State &other) const {
        return time > other.time;
    }
};

int minTimeToReach(int N, int M, vector<int>& G, vector<int>& R, vector<vector<int>>& adj) {
    const int INF = 1e9;
    vector<int> dist(N + 1, INF);
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1] = 0;
    pq.push({1, 0});

    while (!pq.empty()) {
        auto [u, t] = pq.top();
        pq.pop();

        if (u == N) return t;
        if (t > dist[u]) continue;

        for (int v : adj[u]) {
            int arrival = t + 1;  // travel time to v
            int cycle = G[v - 1] + R[v - 1];
            int modt = arrival % cycle;

            int wait = 0;
            if (modt >= G[v - 1]) {
                wait = cycle - modt;
            }

            int nextTime = arrival + wait;

            if (nextTime < dist[v]) {
                dist[v] = nextTime;
                pq.push({v, nextTime});
            }
        }
    }

    return -1; // not reachable
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> G(N), R(N);
    for (int i = 0; i < N; ++i) cin >> G[i];
    for (int i = 0; i < N; ++i) cin >> R[i];

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int U, V;
        cin >> U >> V;
        adj[U].push_back(V);
        adj[V].push_back(U); // bidirectional
    }

    cout << minTimeToReach(N, M, G, R, adj) << endl;
    return 0;
}
