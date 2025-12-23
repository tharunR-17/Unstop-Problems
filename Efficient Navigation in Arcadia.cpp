#include <bits/stdc++.h>
using namespace std;

int processMoves() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rows, cols;
    cin >> rows >> cols;

    int reqRows = rows / 2;
    int reqCols = cols / 2;

    string moves;
    cin >> moves;

    int forward = 0, right = 0;
    for (char move : moves) {
        if (move == 'F') forward++;
        if (move == 'R') right++;
    }

    if (forward < reqRows || right < reqCols) {
        cout << -1 << "\n";
        return 0;
    }

    int essentialMoves = reqRows + reqCols;
    int deletable = moves.size() - essentialMoves;

    cout << deletable << "\n";
    return 0;
}

int main() {
    return processMoves();
}
