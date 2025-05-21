#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

bool solve(const string &s, int a, int b) {
    int n = s.length();
    unordered_set<int> current_scores = {0}; // Start with the score of 0

    for (int i = 0; i < n; ++i) {
        unordered_set<int> next_scores;
        for (int score : current_scores) {
            if (s[i] == '+') {
                next_scores.insert(score + a);
                next_scores.insert(score + b);
            } else {
                next_scores.insert(score - a);
                next_scores.insert(score - b);
            }
        }
        current_scores = move(next_scores);
    }

    // Check if 0 is in the final set of scores
    return current_scores.count(0) > 0;
}

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int rounds;
    cin >> rounds;
    while (rounds--) {
        int a, b;
        cin >> a >> b;
        cout << (solve(s, a, b) ? "YES\n" : "NO\n");
    }

    return 0;
}
