#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up

    int largestIsland(vector<vector<int>>& grid) {
        int N = grid.size();
        int maxSize = 0;
        unordered_map<int, int> islandSize;
        int islandId = 2;

        // Step 1: Identify islands and store sizes
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 1) {
                    int size = iterativeDFS(grid, i, j, islandId);
                    islandSize[islandId] = size;
                    maxSize = max(maxSize, size);
                    islandId++;
                }
            }
        }

        // Step 2: Try converting each 0 to 1 and find the largest island
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> seenIslands;
                    int newSize = 1;
                    for (auto& d : directions) {
                        int ni = i + d[0], nj = j + d[1];
                        if (ni >= 0 && nj >= 0 && ni < N && nj < N && grid[ni][nj] > 1) {
                            int id = grid[ni][nj];
                            if (seenIslands.insert(id).second) {
                                newSize += islandSize[id];
                            }
                        }
                    }
                    maxSize = max(maxSize, newSize);
                }
            }
        }

        return maxSize;
    }

    // **Iterative DFS to avoid stack overflow**
    int iterativeDFS(vector<vector<int>>& grid, int x, int y, int islandId) {
        int size = 0;
        stack<pair<int, int>> st;
        st.push(make_pair(x, y));
        grid[x][y] = islandId;

        while (!st.empty()) {
            pair<int, int> cell = st.top();
            st.pop();
            int i = cell.first, j = cell.second;  // Replacing structured bindings

            size++;

            for (auto& d : directions) {
                int ni = i + d[0], nj = j + d[1];
                if (ni >= 0 && nj >= 0 && ni < grid.size() && nj < grid.size() && grid[ni][nj] == 1) {
                    grid[ni][nj] = islandId;
                    st.push(make_pair(ni, nj));
                }
            }
        }
        return size;
    }
};

int main() {
    int N;
    cin >> N;
    vector<vector<int>> grid(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    Solution solution;
    cout << solution.largestIsland(grid) << endl;

    return 0;
}
