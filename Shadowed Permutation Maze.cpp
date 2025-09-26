#include <iostream>
#include <vector>
using namespace std;

// Function declarations
bool solveMatrix(vector<vector<int>>& matrix, int N);
bool solve(vector<vector<int>>& matrix, int N, int row, int col);
bool isValid(const vector<vector<int>>& matrix, int N);
void printMatrix(const vector<vector<int>>& matrix);

int main() {
    int N;
    cin >> N;

    vector<vector<int>> matrix(N, vector<int>(N));
    
    // Input the matrix
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> matrix[i][j];

    // Solve the matrix
    if (solveMatrix(matrix, N)) {
        printMatrix(matrix);
    } else {
        cout << -1 << endl;
    }

    return 0;
}

bool solveMatrix(vector<vector<int>>& matrix, int N) {
    return solve(matrix, N, 0, 0);
}

bool solve(vector<vector<int>>& matrix, int N, int row, int col) {
    if (row == N) {
        return isValid(matrix, N);
    }

    int nextRow = (col == N - 1) ? row + 1 : row;
    int nextCol = (col == N - 1) ? 0 : col + 1;

    if (matrix[row][col] == 0) {
        for (int num = 1; num <= N; ++num) {
            matrix[row][col] = num;
            if (isValid(matrix, N)) {
                if (solve(matrix, N, nextRow, nextCol)) {
                    return true;
                }
            }
            matrix[row][col] = 0; // backtrack
        }
        return false;
    } else {
        return solve(matrix, N, nextRow, nextCol);
    }
}

bool isValid(const vector<vector<int>>& matrix, int N) {
    for (int i = 0; i < N; ++i) {
        vector<bool> rowCheck(N + 1, false);
        vector<bool> colCheck(N + 1, false);

        for (int j = 0; j < N; ++j) {
            // Check row
            if (matrix[i][j] != 0) {
                if (rowCheck[matrix[i][j]]) return false;
                rowCheck[matrix[i][j]] = true;
            }

            // Check column
            if (matrix[j][i] != 0) {
                if (colCheck[matrix[j][i]]) return false;
                colCheck[matrix[j][i]] = true;
            }
        }
    }
    return true;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}
