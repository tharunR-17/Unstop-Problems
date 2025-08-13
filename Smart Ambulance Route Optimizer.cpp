#include <bits/stdc++.h>
using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int min_turns_to_hospital(int N, int M, const vector<vector<int>>& grid) {
    int start_x = -1, start_y = -1;
    
    for (int i = 0; i < N && start_x == -1; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 3) {
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    vector<vector<vector<int>>> visited(N, vector<vector<int>>(M, vector<int>(4, INT_MAX)));
    queue<tuple<int, int, int, int>> q;

    for (int d = 0; d < 4; ++d) {
        int nx = start_x + dx[d];
        int ny = start_y + dy[d];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] != 1) {
            q.emplace(nx, ny, d, 0); 
            visited[nx][ny][d] = 0;
        }
    }

    int min_turns = INT_MAX;

    while (!q.empty()) {
        auto [x, y, dir, turns] = q.front();
        q.pop();

        if (grid[x][y] == 2) {
            min_turns = min(min_turns, turns);
            continue;
        }

        for (int nd = 0; nd < 4; ++nd) {
            int nx = x + dx[nd];
            int ny = y + dy[nd];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] != 1) {
                int new_turns = turns + (nd != dir ? 1 : 0);
                if (new_turns < visited[nx][ny][nd]) {
                    visited[nx][ny][nd] = new_turns;
                    q.emplace(nx, ny, nd, new_turns);
                }
            }
        }
    }

    return (min_turns == INT_MAX) ? -1 : min_turns;
}

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> grid(N, std::vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            std::cin >> grid[i][j];
        }
    }
    int result = min_turns_to_hospital(N, M, grid);
    std::cout << result << std::endl;
    return 0;
}
