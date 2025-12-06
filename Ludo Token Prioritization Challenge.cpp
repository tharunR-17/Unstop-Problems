#include <iostream>
#include <vector>
using namespace std;

struct Token {
    int position; 
    int moves;    
    bool finished;

    Token() {
        position = -1;  
        moves = 0;
        finished = false;
    }
};

int simulateLudo(int N, const vector<int>& diceRolls) {
    vector<Token> tokens(4);

    for (int roll : diceRolls) {
        vector<int> movable;

        for (int i = 0; i < 4; ++i) {
            if (tokens[i].finished) continue;

            if (tokens[i].position == -1 && roll == 6) {
                movable.push_back(i);
            }
            else if (tokens[i].position != -1) {
                movable.push_back(i);
            }
        }

        if (movable.empty()) continue;

        int best = movable[0];
        for (int idx : movable) {
            Token& a = tokens[idx];
            Token& b = tokens[best];

            if (a.position > b.position) {
                best = idx;
            } else if (a.position == b.position) {
                if (a.moves < b.moves) {
                    best = idx;
                } else if (a.moves == b.moves && idx < best) {
                    best = idx;
                }
            }
        }

        Token& t = tokens[best];
        if (t.position == -1) {
            t.position = 0; 
        } else {
            t.position += roll;
            if (t.position >= N - 1) {
                t.position = N - 1;
                t.finished = true;
            }
        }
        t.moves++;
    }

    int count = 0;
    for (const Token& t : tokens) {
        if (t.finished) count++;
    }

    return count;
}

int main() {
    int N, R;
    cin >> N >> R;
    vector<int> dice(R);
    for (int i = 0; i < R; ++i) {
        cin >> dice[i];
    }

    int result = simulateLudo(N, dice);
    cout << result << endl;
    return 0;
}
