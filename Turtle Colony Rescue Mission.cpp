#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

static const int INF = 1e9;

int rescue_turtles(vector<vector<char>> &grid, int sx, int sy) {
    int n = (int)grid.size();
    int m = (int)grid[0].size();

    // Collect positions: node 0 = start, nodes 1..k = turtles
    vector<pair<int,int>> nodes;
    nodes.push_back({sx, sy});
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == 'T')
                nodes.push_back({i, j});

    int k = (int)nodes.size() - 1; // number of turtles

    // If no turtles, zero steps needed
    if (k == 0) return 0;

    // If start is a wall, impossible unless k==0 (already handled)
    if (grid[sx][sy] == '#') return -1;

    // BFS from each node to compute pairwise distances
    auto bfs_from = [&](int si, int sj) {
        vector<vector<int>> dist(n, vector<int>(m, INF));
        queue<pair<int,int>> q;
        if (si >= 0 && si < n && sj >= 0 && sj < m && grid[si][sj] != '#') {
            dist[si][sj] = 0;
            q.push({si, sj});
        }
        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};
        while (!q.empty()) {
            auto [x,y] = q.front(); q.pop();
            for (int dir = 0; dir < 4; ++dir) {
                int nx = x + dx[dir], ny = y + dy[dir];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if (grid[nx][ny] == '#') continue;
                if (dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return dist;
    };

    int N = k + 1; // total nodes including start
    vector<vector<int>> D(N, vector<int>(N, INF));

    // Build pairwise distance matrix D
    for (int idx = 0; idx < N; ++idx) {
        auto [xi, yi] = nodes[idx];
        auto dist = bfs_from(xi, yi);
        for (int j = 0; j < N; ++j) {
            auto [xj, yj] = nodes[j];
            D[idx][j] = dist[xj][yj];
        }
    }

    // If any turtle unreachable from start or needed transitions are INF, DP will find -1 naturally,
    // but we can early check: if start->turtle is INF for any turtle, it's impossible.
    for (int t = 1; t <= k; ++t) {
        if (D[0][t] >= INF) return -1;
    }

    // Bitmask DP: dp[mask][i], mask over k turtles (1..k), i in [0..k] (current node index)
    int FULL = (1 << k) - 1;
    vector<vector<int>> dp(1 << k, vector<int>(N, INF));
    dp[0][0] = 0; // start at start, visited no turtles

    for (int mask = 0; mask <= FULL; ++mask) {
        for (int i = 0; i < N; ++i) {
            if (dp[mask][i] >= INF) continue;
            // try to go to an unvisited turtle j (node index = j, turtle bit = j-1)
            for (int j = 1; j <= k; ++j) {
                int bit = j - 1;
                if (mask & (1 << bit)) continue; // already visited this turtle
                if (D[i][j] >= INF) continue;    // unreachable transition
                int nmask = mask | (1 << bit);
                dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + D[i][j]);
            }
        }
    }

    int ans = INF;
    for (int last = 1; last <= k; ++last) {
        ans = min(ans, dp[FULL][last]);
    }

    return (ans >= INF ? -1 : ans);
}

int main() {
    int n, m, sx, sy;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];
    cin >> sx >> sy;
    int result = rescue_turtles(grid, sx, sy);
    cout << result << endl;
    return 0;
}
