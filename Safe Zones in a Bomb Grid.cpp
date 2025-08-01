#include <iostream>
#include <vector>
using namespace std;

int count_safe_zones(vector<vector<char>>& grid, int n, int m) {
    // Your logic will go here
    int cnt0 = 0;
    vector<pair<int, int>> bombs;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '0') cnt0++;
            if (grid[i][j] == 'B') bombs.push_back({i, j});
        }
    }
    for (auto [i, j] : bombs) {
        for (int col = j - 1; col >= 0; col--) {
            if (grid[i][col] == 'W') break;
            if (grid[i][col] == '0') {
                grid[i][col] = 'X';
                cnt0--;
            }
        }
        for (int col = j + 1; col < m; col++) {
            if (grid[i][col] == 'W') break;
            if (grid[i][col] == '0') {
                grid[i][col] = 'X';
                cnt0--;
            }
        }
        for (int row = i - 1; row >= 0; row--) {
            if (grid[row][j] == 'W') break;
            if (grid[row][j] == '0') {
                grid[row][j] = 'X';
                cnt0--;
            }
        }
        for (int row = i + 1; row < n; row++) {
            if (grid[row][j] == 'W') break;
            if (grid[row][j] == '0') {
                grid[row][j] = 'X';
                cnt0--;
            }
        }
    }

    return cnt0;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int result = count_safe_zones(grid, n, m);
    cout << result << endl;
    return 0;
}
