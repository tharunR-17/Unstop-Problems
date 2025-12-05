#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int GRID_SIZE = 5;

vector<pair<int,int>> getZoneCells(int r, int c) {
    vector<pair<int,int>> zone;
    for (int i = r - 1; i <= r + 1; ++i) {
        for (int j = c - 1; j <= c + 1; ++j) {
            if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE) {
                zone.emplace_back(i, j);
            }
        }
    }
    return zone;
}

string switchPlayer(const string& current) {
    return current == "X" ? "O" : "X";
}

string playGame(int N, const vector<pair<int, int>>& moves) {
    string board[GRID_SIZE][GRID_SIZE];
    string zoneOwner[GRID_SIZE][GRID_SIZE];

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            board[i][j] = "";
            zoneOwner[i][j] = "";
        }
    }

    string currentPlayer = "X";

    for (const auto& move : moves) {
        int r = move.first, c = move.second;

        if (!board[r][c].empty()) {
            currentPlayer = switchPlayer(currentPlayer);
            continue;
        }
        vector<pair<int,int>> zoneCells = getZoneCells(r, c);
        bool conflict = false;
        for (const auto& cell : zoneCells) {
            int x = cell.first, y = cell.second;
            if (!zoneOwner[x][y].empty() && zoneOwner[x][y] != currentPlayer) {
                conflict = true;
                break;
            }
        }

        if (conflict) {
            currentPlayer = switchPlayer(currentPlayer);
            continue;
        }

        board[r][c] = currentPlayer;
        for (const auto& cell : zoneCells) {
            zoneOwner[cell.first][cell.second] = currentPlayer;
        }

        currentPlayer = switchPlayer(currentPlayer);
    }
    int xCount = 0, oCount = 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (zoneOwner[i][j] == "X") xCount++;
            else if (zoneOwner[i][j] == "O") oCount++;
        }
    }

    if (xCount > oCount) return "X";
    else if (oCount > xCount) return "O";
    else return "Draw";
}

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> moves;
    for (int i = 0; i < N; ++i) {
        int r, c;
        cin >> r >> c;
        moves.emplace_back(r, c);
    }

    string result = playGame(N, moves);
    cout << result << endl;

    return 0;
}
