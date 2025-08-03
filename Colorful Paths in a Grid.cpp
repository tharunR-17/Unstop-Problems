#include <iostream>
#include <vector>
#include <unordered_set>
#define MOD 1000000007

using namespace std;

void dfs(int i, int j, int n, int m, vector<string>& grid, string path, unordered_set<string>& sequences) {
    path += grid[i][j];
    
    if (i == n - 1 && j == m - 1) {
        sequences.insert(path);
        return;
    }
    
    if (i + 1 < n) dfs(i + 1, j, n, m, grid, path, sequences);
    if (j + 1 < m) dfs(i, j + 1, n, m, grid, path, sequences);
}

int count_distinct_color_sequences(int n, int m, vector<string>& grid) {
    unordered_set<string> sequences;
    dfs(0, 0, n, m, grid, "", sequences);
    return sequences.size() % MOD;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
        cin >> grid[i];
    }
    int result = count_distinct_color_sequences(N, M, grid);
    cout << result << endl;
    return 0;
}
