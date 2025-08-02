#include <bits/stdc++.h>
using namespace std;

struct State {
    int x, y, steps;
    unordered_map<int, int> blocked;

    State(int x, int y, int steps, const unordered_map<int, int> &blocked) 
        : x(x), y(y), steps(steps), blocked(blocked) {}

    string encodeBlocked() const {
        vector<pair<int, int>> active;
        for (auto &p : blocked) {
            if (p.second > 0)
                active.push_back(p);
        }
        sort(active.begin(), active.end());
        string s;
        for (auto &[cell, time] : active) {
            s += to_string(cell) + ":" + to_string(time) + ",";
        }
        return s;
    }
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int n, m, K;
vector<string> grid;

int cellId(int x, int y) {
    return x * m + y;
}

int bfs(int sx, int sy, int tx, int ty) {
    queue<State> q;
    set<string> visited;

    unordered_map<int, int> initialBlocked;
    State start(sx, sy, 0, initialBlocked);

    string initialKey = to_string(sx) + "," + to_string(sy) + "|" + start.encodeBlocked();
    q.push(start);
    visited.insert(initialKey);

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.x == tx && curr.y == ty) return curr.steps;

        unordered_map<int, int> updatedBlocked;
        for (auto &[id, time] : curr.blocked) {
            if (time > 1)
                updatedBlocked[id] = time - 1;
        }

        for (int dir = 0; dir < 4; ++dir) {
            int nx = curr.x + dx[dir];
            int ny = curr.y + dy[dir];

            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (grid[nx][ny] == 'T') continue;

            int nextId = cellId(nx, ny);
            if (updatedBlocked.count(nextId)) continue;

            unordered_map<int, int> nextBlocked = updatedBlocked;

            if (grid[nx][ny] == 'E') {
                for (int d = 0; d < 4; ++d) {
                    int ex = nx + dx[d], ey = ny + dy[d];
                    if (ex >= 0 && ex < n && ey >= 0 && ey < m && grid[ex][ey] != 'T') {
                        nextBlocked[cellId(ex, ey)] = K;
                    }
                }
            }

            string stateKey = to_string(nx) + "," + to_string(ny) + "|";
            vector<pair<int, int>> sortedBlocked(nextBlocked.begin(), nextBlocked.end());
            sort(sortedBlocked.begin(), sortedBlocked.end());
            for (auto &[id, t] : sortedBlocked)
                stateKey += to_string(id) + ":" + to_string(t) + ",";

            if (visited.count(stateKey) == 0) {
                visited.insert(stateKey);
                q.emplace(nx, ny, curr.steps + 1, nextBlocked);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> K;
    grid.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    sx--; sy--; tx--; ty--;

    cout << bfs(sx, sy, tx, ty) << "\n";
    return 0;
}
