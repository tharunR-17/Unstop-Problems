#include <bits/stdc++.h>
using namespace std;

bool isSudokuValid(vector<vector<char>>& board, int row, int col, char ch) {

    for(int j=0; j<9; j++) {
        if(board[row][j] == ch) return false; 
    }

    for(int i=0; i<9; i++) {
        if(board[i][col] == ch) return false;
    }

    int subRow = (row/3)*3, subCol = (col/3)*3;
    for(int i=subRow; i<subRow + 3; i++) {
        for(int j=subCol; j < subCol + 3; j++) {
            if(board[i][j] == ch) return false;
        }
    }
    return true;
}

bool solveSudoku(vector<vector<char>>& board, int row, int col) {

    if(row == 9) return 1;

    int nextRow = (col == 8) ? row + 1 : row;
    int nextCol = (col == 8) ? 0 : col+1;

    if(board[row][col] != '.') {
        bool resp = solveSudoku(board, nextRow, nextCol);
        if(resp) return 1;
    } else {

        for(int i=1; i<=9; i++) {
            if(isSudokuValid(board, row, col, (char)(i + '0'))) {
                board[row][col] = (char)(i+'0');
                bool resp = solveSudoku(board, nextRow, nextCol);
                if(resp) return 1;
                board[row][col] = '.';
            }
        }
    }
    return 0;
}

void solveSudoku(vector<vector<char>>& board) {

    vector<vector<char>> originalBoard(9, vector<char>(9));
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            originalBoard[i][j] = board[i][j];
        }
    }

    if(solveSudoku(board, 0, 0)) return;

    board = originalBoard;
}
 
int main() {
    

    vector<vector<char>> vec(9, vector<char>(9));
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            cin>>vec[i][j];
        }
    }

    solveSudoku(vec);
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            cout<<vec[i][j] <<" ";
        }
        cout<<endl;
    }
    return 0;
}
