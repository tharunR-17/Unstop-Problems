#include <iostream>
#include <vector>
using namespace std;

int circuitReconfiguration(vector<vector<int>>& grid) {
    int n = grid.size();

    // Base power values
    int power[4] = {0, 3, 5, 7};

    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;

    long long step = 1;
    long long totalQuality = 0;

    while (top <= bottom && left <= right) {
        
        // Move right
        for (int col = left; col <= right; col++) {
            totalQuality += power[grid[top][col]] * step;
            step++;
        }
        top++;

        // Move down
        for (int row = top; row <= bottom; row++) {
            totalQuality += power[grid[row][right]] * step;
            step++;
        }
        right--;

        if (top <= bottom) {
            // Move left
            for (int col = right; col >= left; col--) {
                totalQuality += power[grid[bottom][col]] * step;
                step++;
            }
            bottom--;
        }

        if (left <= right) {
            // Move up
            for (int row = bottom; row >= top; row--) {
                totalQuality += power[grid[row][left]] * step;
                step++;
            }
            left++;
        }
    }

    return totalQuality;
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

    int result = circuitReconfiguration(grid);
    cout << result << endl;

    return 0;
}
