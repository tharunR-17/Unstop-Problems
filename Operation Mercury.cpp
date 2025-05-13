#include <iostream>
#include <vector>
using namespace std;
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

const int MAX_H = 1000;
const int MAX_W = 1000;

int visitId = 1; // used to mark visited cells
int visited[MAX_H][MAX_W]; // shared across all queries
void user_logic(int H, int W, vector<vector<int>>& grid, vector<tuple<int, int, int>>& queries, vector<int>& result) {
    const int dir[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    static int visited[MAX_H][MAX_W] = {0};
    static int visitId = 1;

    for (int q = 0; q < queries.size(); ++q) {
        int r = get<0>(queries[q]) - 1;
        int c = get<1>(queries[q]) - 1;
        int p = get<2>(queries[q]);

        if (grid[r][c] >= p) {
            result[q] = 0;
            continue;
        }

        int count = 0;
        queue<pair<int, int>> q_cells;
        q_cells.push(make_pair(r, c));
        visited[r][c] = visitId;

        while (!q_cells.empty()) {
            int x = q_cells.front().first;
            int y = q_cells.front().second;
            q_cells.pop();
            count++;

            for (int d = 0; d < 4; ++d) {
                int nx = x + dir[d][0];
                int ny = y + dir[d][1];

                if (nx >= 0 && nx < H && ny >= 0 && ny < W &&
                    visited[nx][ny] != visitId &&
                    grid[nx][ny] < p) {
                    
                    visited[nx][ny] = visitId;
                    q_cells.push(make_pair(nx, ny));
                }
            }
        }

        result[q] = count;
        visitId++;
    }
}



int main() {
    int H, W, Q;
    cin >> H >> W >> Q;
    
    vector<vector<int>> grid(H, vector<int>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }
    
    vector<tuple<int, int, int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        int r, c, p;
        cin >> r >> c >> p;
        queries[i] = make_tuple(r, c, p);
    }
    
    vector<int> result(Q);
    user_logic(H, W, grid, queries, result);
    
    for (int i = 0; i < Q; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}
