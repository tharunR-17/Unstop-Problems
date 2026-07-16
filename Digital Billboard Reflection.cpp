#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int R, C;
    cin >> R >> C;

    vector<vector<int>> matrix(R, vector<int>(C));

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < R; i++) {
        for (int j = C - 1; j >= 0; j--) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
