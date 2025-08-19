#include <bits/stdc++.h>
using namespace std;

struct Flight {
    int to;
    int distance;
};

struct State {
    int city;
    int refuels;
    int fuelLeft;

    bool operator>(const State& other) const {
        return refuels > other.refuels;
    }
};

int minRefuels(int N, int M, int D, int S, int E, vector<vector<int>> &flights) {
    vector<vector<pair<int, int>>> graph(N + 1);
    for (auto& f : flights) {
        int u = f[0], v = f[1], dist = f[2];
        if (dist <= D) {  
            graph[u].emplace_back(v, dist);
        }
    }
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({S, 0, D});
    vector<vector<bool>> visited(N + 1, vector<bool>(D + 1, false));

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        int city = curr.city, refuels = curr.refuels, fuel = curr.fuelLeft;

        if (city == E) return refuels;

        if (visited[city][fuel]) continue;
        visited[city][fuel] = true;

        for (auto& [next, dist] : graph[city]) {
            if (dist <= fuel) {
                pq.push({next, refuels, fuel - dist});
            }

            if (dist <= D) {
                pq.push({next, refuels + 1, D - dist});
            }
        }
    }

    return -1; 
}

int main() {
    int N, M, D;
    cin >> N >> M >> D;

    int S, E;
    cin >> S >> E;

    vector<vector<int>> flights(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        cin >> flights[i][0] >> flights[i][1] >> flights[i][2];
    }

    int result = minRefuels(N, M, D, S, E, flights);
    cout << result << endl;

    return 0;
}
