#include <bits/stdc++.h>
using namespace std;

struct Compare {
    bool operator()(const pair<int, string>& a,
                    const pair<int, string>& b) const {
        if (a.first != b.first) {
            return a.first > b.first;
        }
        return a.second < b.second;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, C;
    cin >> n >> C;

    unordered_map<string, int> freq;
    set<pair<int, string>, Compare> ranking;

    for (int i = 0; i < n; i++) {
        char type;
        cin >> type;

        if (type == 'S') {
            string name;
            cin >> name;

            int oldCount = freq[name];

            if (oldCount > 0) {
                ranking.erase({oldCount, name});
            }

            freq[name] = oldCount + 1;
            ranking.insert({oldCount + 1, name});
        }
        else if (type == 'R') {
            int printed = 0;

            for (const auto& entry : ranking) {
                if (printed == C) {
                    break;
                }

                if (printed > 0) {
                    cout << ' ';
                }

                cout << entry.second;
                printed++;
            }

            cout << '\n';
        }
    }

    return 0;
}
