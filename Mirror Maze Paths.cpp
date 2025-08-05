#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int simulateLaserBeam(int N, int M, const vector<string>& grid)
{
    // Directions: Right, Down, Left, Up
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    // Direction change mappings for mirrors
    // For '/', the direction changes as: 0->3, 1->2, 2->1, 3->0
    // For '\', the direction changes as: 0->1, 1->0, 2->3, 3->2
    int mirrorSlash[]     = {3, 2, 1, 0};
    int mirrorBackslash[] = {1, 0, 3, 2};

    // Visited[x][y][dir]: whether (x,y) has been visited from direction `dir`
    vector<vector<vector<bool>>> visited(N, vector<vector<bool>>(M, vector<bool>(4, false)));

    int x = 0, y = 0, dir = 0;  // Start at (0,0) going right
    set<pair<int, int>> uniqueCells;

    while (true)
    {
        // Check boundaries
        if (x < 0 || x >= N || y < 0 || y >= M)
            break;

        // If we've visited this cell in the same direction, it's a loop
        if (visited[x][y][dir])
            return -1;

        visited[x][y][dir] = true;
        uniqueCells.insert({x, y}); // track unique cells visited

        char cell = grid[x][y];

        if (cell == '/')
            dir = mirrorSlash[dir];
        else if (cell == '\\')
            dir = mirrorBackslash[dir];

        x += dx[dir];
        y += dy[dir];
    }

    return uniqueCells.size();
}


int main() {
    int N, M;
    cin >> N >> M;
    
    vector<string> grid(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }
    
    int result = simulateLaserBeam(N, M, grid);
    cout << result << endl;

    return 0;
}
