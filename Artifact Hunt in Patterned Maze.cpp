#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m; 
vector<string> g;
string p;
int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; 

int dfs(int i, int j, int idx, vector<vector<bool>>& vis) {
    if (idx == p.size()) return 1; 
    int count = 0;
    vis[i][j] = true;
    for (int d = 0; d < 4; ++d) {
        int ni = i + dirs[d][0];
        int nj = j + dirs[d][1];
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && !vis[ni][nj] && g[ni][nj] == p[idx]) {
            count += dfs(ni, nj, idx + 1, vis);
        }
    }
    vis[i][j] = false;
    return count;
}

// Placeholder function where the user will implement their logic
int countPatternPaths(const vector<string>& grid, const string& pattern) {
    // User should write their logic here
    // Parameters:
    // - grid: A 2D vector of characters representing the grid
    // - pattern: A string representing the pattern to be matched
    // Return:
    // - An integer representing the total number of distinct complete paths that match the pattern exactly
    g = grid;
    p = pattern;
    n = g.size();
    m = g[0].size();
    int total = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == p[0]) {
                vector<vector<bool>> vis(n, vector<bool>(m, false));
                total += dfs(i, j, 1, vis); // start from index 1 since p[0] is already matched
            }
        }
    }

    return total;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }
    
    string pattern;
    cin >> pattern;
    
    // Call the user logic function and print the output
    int result = countPatternPaths(grid, pattern);
    cout << result << endl;
    
    return 0;
}
