#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int rows, cols;
vector<vector<char>> matrix;
vector<vector<bool>> seen;

void explore(int i, int j) {
    queue<pair<int, int>> bfsQueue;
    bfsQueue.push({i, j});
    seen[i][j] = true;

    const int dirX[4] = {0, 0, -1, 1};
    const int dirY[4] = {-1, 1, 0, 0};

    while (!bfsQueue.empty()) {
        auto current = bfsQueue.front();
        bfsQueue.pop();

        for (int d = 0; d < 4; ++d) {
            int ni = current.first + dirX[d];
            int nj = current.second + dirY[d];

            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {
                if (!seen[ni][nj] && matrix[ni][nj] == '1') {
                    seen[ni][nj] = true;
                    bfsQueue.push({ni, nj});
                }
            }
        }
    }
}

int main() {
    cin >> rows >> cols;
    matrix.resize(rows, vector<char>(cols));
    seen.assign(rows, vector<bool>(cols, false));

    for (int i = 0; i < rows; ++i) {
        string input;
        cin >> input;
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = input[j];
        }
    }

    int componentCount = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == '1' && !seen[i][j]) {
                explore(i, j);
                ++componentCount;
            }
        }
    }

    cout << componentCount << '\n';
    return 0;
}
