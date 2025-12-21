#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
using namespace std;

bool checkPrime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; i <= sqrt(x); i += 2)
        if (x % i == 0) return false;
    return true;
}

bool checkSquare(int x) {
    int r = sqrt(x);
    return r * r == x;
}

void updateGrid(vector<vector<int>>& grid, int size, int& fullRows, int& zeroCount) {
    vector<vector<int>> backup = grid;
    vector<vector<bool>> flags(size, vector<bool>(size, false));
    unordered_set<int> rSet, cSet;

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (checkPrime(grid[i][j])) {
                backup[i][j] = 0;
                zeroCount++;
            }

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (checkSquare(grid[i][j])) {
                rSet.insert(i);
                cSet.insert(j);
            }

    for (int r : rSet)
        for (int j = 0; j < size; ++j)
            flags[r][j] = true;

    for (int c : cSet)
        for (int i = 0; i < size; ++i)
            flags[i][c] = true;

    grid = backup;
    for (int i = 0; i < size; ++i) {
        bool allNeg = true;
        for (int j = 0; j < size; ++j) {
            if (flags[i][j]) grid[i][j] = -1;
            if (grid[i][j] != -1) allNeg = false;
        }
        if (allNeg) fullRows++;
    }

    zeroCount = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (grid[i][j] == 0)
                zeroCount++;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];

    int rowsMarked = 0, primesMarked = 0;
    updateGrid(mat, n, rowsMarked, primesMarked);

    cout << rowsMarked << " " << primesMarked << endl;
    for (const auto& r : mat) {
        for (int v : r) cout << v << " ";
        cout << endl;
    }

    return 0;
}
