#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
    int gridSize;
    int rowDelta[4] = {-1, 1, 0, 0};
    int colDelta[4] = {0, 0, -1, 1};
    map<int, int> componentSizes;

    bool inBounds(int coord) {
        return coord >= 0 && coord < gridSize;
    }
    
    bool isCellValid(int r, int c) {
        return inBounds(r) && inBounds(c);
    }

    int findAndLabelIsland(int r, int c, int componentId, vector<vector<int>>& grid) {
        if (!isCellValid(r, c) || grid[r][c] != 1) {
            return 0; 
        }
        
        grid[r][c] = componentId;
        int currentArea = 1;

        for (int i = 0; i < 4; ++i) {
            currentArea += findAndLabelIsland(r + rowDelta[i], c + colDelta[i], componentId, grid);
        }
        
        return currentArea;
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        gridSize = grid.size();
        if (gridSize == 0) return 0;

        int componentId = 2; 
        int maxArea = 0;

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid[i][j] == 1) { 
                    int area = findAndLabelIsland(i, j, componentId, grid);
                    componentSizes[componentId] = area;
                    maxArea = max(maxArea, area);
                    componentId++;
                }
            }
        }
        
        if (maxArea == 0) {
            return 1; 
        }

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid[i][j] == 0) { 
                    set<int> adjacentComponents;
                    int potentialNewArea = 1; 

                    for (int k = 0; k < 4; ++k) {
                        int nextRow = i + rowDelta[k];
                        int nextCol = j + colDelta[k];
                        if (isCellValid(nextRow, nextCol) && grid[nextRow][nextCol] > 1) {
                            adjacentComponents.insert(grid[nextRow][nextCol]);
                        }
                    }

                    for (int id : adjacentComponents) {
                        potentialNewArea += componentSizes[id];
                    }
                    maxArea = max(maxArea, potentialNewArea);
                }
            }
        }

        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if (grid[i][j] != 0) continue; 

                // Horiz. L=2
                if (inBounds(j - 1) && inBounds(j + 2) &&
                    grid[i][j + 1] == 0 &&              
                    grid[i][j - 1] > 1 &&               
                    grid[i][j + 2] > 1 &&               
                    grid[i][j - 1] != grid[i][j + 2] && 
                    (!inBounds(i - 1) || (grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0)) && 
                    (!inBounds(i + 1) || (grid[i + 1][j] == 0 && grid[i + 1][j + 1] == 0))) { 
                    
                    int area = componentSizes[grid[i][j - 1]] + componentSizes[grid[i][j + 2]] + 2;
                    maxArea = max(maxArea, area);
                }

                // Vert. L=2
                if (inBounds(i - 1) && inBounds(i + 2) &&
                    grid[i + 1][j] == 0 &&              
                    grid[i - 1][j] > 1 &&               
                    grid[i + 2][j] > 1 &&               
                    grid[i - 1][j] != grid[i + 2][j] && 
                    (!inBounds(j - 1) || (grid[i][j - 1] == 0 && grid[i + 1][j - 1] == 0)) && 
                    (!inBounds(j + 1) || (grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0))) { 
                    
                    int area = componentSizes[grid[i - 1][j]] + componentSizes[grid[i + 2][j]] + 2;
                    maxArea = max(maxArea, area);
                }

                // Horiz. L=3
                if (inBounds(j - 1) && inBounds(j + 3) &&
                    grid[i][j + 1] == 0 && grid[i][j + 2] == 0 && 
                    grid[i][j - 1] > 1 &&                       
                    grid[i][j + 3] > 1 &&                       
                    grid[i][j - 1] != grid[i][j + 3] &&         
                    (!inBounds(i - 1) || (grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i - 1][j + 2] == 0)) && 
                    (!inBounds(i + 1) || (grid[i + 1][j] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 1][j + 2] == 0))) { 

                    int area = componentSizes[grid[i][j - 1]] + componentSizes[grid[i][j + 3]] + 3;
                    maxArea = max(maxArea, area);
                }

                // Vert. L=3
                if (inBounds(i - 1) && inBounds(i + 3) &&
                    grid[i + 1][j] == 0 && grid[i + 2][j] == 0 && 
                    grid[i - 1][j] > 1 &&                       
                    grid[i + 3][j] > 1 &&                       
                    grid[i - 1][j] != grid[i + 3][j] &&         
                    (!inBounds(j - 1) || (grid[i][j - 1] == 0 && grid[i + 1][j - 1] == 0 && grid[i + 2][j - 1] == 0)) && 
                    (!inBounds(j + 1) || (grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 2][j + 1] == 0))) { 

                    int area = componentSizes[grid[i - 1][j]] + componentSizes[grid[i + 3][j]] + 3;
                    maxArea = max(maxArea, area);
                }
            }
        }
        
        return maxArea;
    }
};


int largestIsland(vector<vector<int>>& grid) {
    Solution sol;
    return sol.largestIsland(grid);
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
    
    int result = largestIsland(grid);
    cout << result << endl;
    
    return 0;
}
