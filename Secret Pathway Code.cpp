#include <bits/stdc++.h>
using namespace std;


// Placeholder function for user logic
string findLexSmallestPath(const vector<string>& grid, int n) {
    // Write your logic here
    // Parameters:
    // - grid: A vector of strings representing the grid
    // - n: An integer representing the size of the grid
    // Return:
    // - A string representing the lexicographically smallest path

    priority_queue<tuple<string, int, int>, vector<tuple<string, int, int>>, greater<>> pq;
    set<pair<int, int>> visited;

    pq.push({string(1, grid[0][0]), 0, 0});
    visited.insert({0, 0});

    while (!pq.empty()) {
        auto [path, i, j] = pq.top();
        pq.pop();

        if (i == n - 1 && j == n - 1) {
            return path;
        }
        if (j + 1 < n && !visited.count({i, j + 1})) {
            pq.push({path + grid[i][j + 1], i, j + 1});
            visited.insert({i, j + 1});
        }
        if (i + 1 < n && !visited.count({i + 1, j})) {
            pq.push({path + grid[i + 1][j], i + 1, j});
            visited.insert({i + 1, j});
        }
    }
    return ""; 
}

int main() {
    int n;
    cin >> n;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // Call user logic function and print the output
    string result = findLexSmallestPath(grid, n);
    cout << result << endl;

    return 0;
}
