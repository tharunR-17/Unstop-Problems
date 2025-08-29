#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Helper DFS to mark an island and calculate its area
int dfs(vector<vector<int>>& grid, int i, int j, int id, int n) {
    if (i < 0 || j < 0 || i >= n || j >= n || grid[i][j] != 1) return 0;
    grid[i][j] = id;
    int area = 1;
    area += dfs(grid, i + 1, j, id, n);
    area += dfs(grid, i - 1, j, id, n);
    area += dfs(grid, i, j + 1, id, n);
    area += dfs(grid, i, j - 1, id, n);
    return area;
}

int largestIsland(vector<vector<int>>& grid) {
    int n = grid.size();
    unordered_map<int, int> area; // islandId -> size
    int id = 2;                   // start labeling islands from 2
    int maxArea = 0;

    // Step 1: Label each island and record its size
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                int a = dfs(grid, i, j, id, n);
                area[id] = a;
                maxArea = max(maxArea, a);
                id++;
            }
        }
    }

    // Step 2: Try flipping each 0 -> 1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                unordered_set<int> seen;
                int newArea = 1; // this flipped cell
                if (i > 0 && grid[i - 1][j] > 1 && !seen.count(grid[i - 1][j])) {
                    newArea += area[grid[i - 1][j]];
                    seen.insert(grid[i - 1][j]);
                }
                if (i < n - 1 && grid[i + 1][j] > 1 && !seen.count(grid[i + 1][j])) {
                    newArea += area[grid[i + 1][j]];
                    seen.insert(grid[i + 1][j]);
                }
                if (j > 0 && grid[i][j - 1] > 1 && !seen.count(grid[i][j - 1])) {
                    newArea += area[grid[i][j - 1]];
                    seen.insert(grid[i][j - 1]);
                }
                if (j < n - 1 && grid[i][j + 1] > 1 && !seen.count(grid[i][j + 1])) {
                    newArea += area[grid[i][j + 1]];
                    seen.insert(grid[i][j + 1]);
                }
                maxArea = max(maxArea, newArea);
            }
        }
    }

    // Step 3: If no 0 found, return n*n
    return (maxArea == 0 ? n * n : maxArea);
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    cout << largestIsland(grid) << endl;

    return 0;
}
