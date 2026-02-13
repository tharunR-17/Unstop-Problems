#include <bits/stdc++.h>
using namespace std;

struct State {
    int cost, r, c, jumps;
    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    int P;
    cin >> P;

    vector<int> portals(P);
    unordered_set<int> portalSet;
    for (int i = 0; i < P; i++) {
        cin >> portals[i];
        portalSet.insert(portals[i]);
    }

    int k;
    cin >> k;

    // Map portal value -> list of cells
    unordered_map<int, vector<pair<int,int>>> portalCells;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (portalSet.count(grid[i][j])) {
                portalCells[grid[i][j]].push_back({i, j});
            }
        }
    }

    const int INF = 1e9;
    vector<vector<vector<int>>> dist(m,
        vector<vector<int>>(n, vector<int>(k + 1, INF)));

    priority_queue<State, vector<State>, greater<State>> pq;

    dist[0][0][0] = 0;
    pq.push({0, 0, 0, 0});

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.cost != dist[cur.r][cur.c][cur.jumps])
            continue;

        // Reached destination
        if (cur.r == m - 1 && cur.c == n - 1) {
            cout << cur.cost << "\n";
            return 0;
        }

        // Normal moves
        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];

            if (nr < 0 || nc < 0 || nr >= m || nc >= n)
                continue;

            int newCost = cur.cost + grid[nr][nc];

            if (newCost < dist[nr][nc][cur.jumps]) {
                dist[nr][nc][cur.jumps] = newCost;
                pq.push({newCost, nr, nc, cur.jumps});
            }
        }

        // Portal moves
        int val = grid[cur.r][cur.c];
        if (portalSet.count(val) && cur.jumps < k) {
            for (auto &cell : portalCells[val]) {
                int nr = cell.first;
                int nc = cell.second;

                if (nr == cur.r && nc == cur.c)
                    continue;

                if (cur.cost < dist[nr][nc][cur.jumps + 1]) {
                    dist[nr][nc][cur.jumps + 1] = cur.cost;
                    pq.push({cur.cost, nr, nc, cur.jumps + 1});
                }
            }
        }
    }

    cout << -1 << "\n";
    return 0;
}
