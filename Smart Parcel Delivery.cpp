#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, pair<int, int>> Node; // {cost, {row, col}}

int minEnergyToDestination(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();

    if (grid[0][0] == -1 || grid[n - 1][m - 1] == -1)
        return -1;

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[0][0] = grid[0][0];
    pq.push(make_pair(grid[0][0], make_pair(0, 0)));

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Node current = pq.top(); pq.pop();
        int cost = current.first;
        int x = current.second.first;
        int y = current.second.second;

        if (x == n - 1 && y == m - 1)
            return cost;

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] != -1) {
                int newCost = cost + grid[nx][ny];
                if (newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    pq.push(make_pair(newCost, make_pair(nx, ny)));
                }
            }
        }
    }

    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];

    cout << minEnergyToDestination(grid) << endl;
    return 0;
}
