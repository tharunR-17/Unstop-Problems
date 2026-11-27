#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Change {
    int idx;
    ll oldValue;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;

    vector<string> tokens(m);
    vector<ll> keys;

    // Read all tokens and collect parameter numbers
    for (int i = 0; i < m; i++) {
        cin >> tokens[i];

        string s = tokens[i];

        if (s[0] == 'S' || s[0] == 'G') {
            int pos = 1;

            while (pos < (int)s.size() &&
                   isdigit(s[pos])) {
                pos++;
            }

            ll k = stoll(s.substr(1, pos - 1));
            keys.push_back(k);
        }
    }

    // Coordinate compression
    sort(keys.begin(), keys.end());
    keys.erase(unique(keys.begin(), keys.end()), keys.end());

    int n = keys.size();

    vector<ll> value(n, -1);

    // History of modifications
    vector<Change> history;

    // Stores history size at the beginning of each session
    vector<int> sessions;

    ll total = 0;

    // Process tokens
    for (string s : tokens) {

        if (s[0] == 'S') {
            // S k=v
            int pos = s.find('=');

            ll k = stoll(s.substr(1, pos - 1));
            ll v = stoll(s.substr(pos + 1));

            int idx = lower_bound(
                keys.begin(), keys.end(), k
            ) - keys.begin();

            // Save previous state
            history.push_back({idx, value[idx]});

            // Update total sum
            if (value[idx] != -1) {
                total -= value[idx];
            }

            value[idx] = v;
            total += v;
        }

        else if (s[0] == 'G') {
            // G k
            ll k = stoll(s.substr(1));

            int idx = lower_bound(
                keys.begin(), keys.end(), k
            ) - keys.begin();

            cout << value[idx] << " ";
        }

        else if (s == "T") {
            // Total sum
            cout << total << " ";
        }

        else if (s == "B") {
            // Begin a new session
            sessions.push_back(history.size());
        }

        else if (s == "D") {
            // Discard current session
            int start = sessions.back();
            sessions.pop_back();

            // Roll back all changes
            while ((int)history.size() > start) {

                Change c = history.back();
                history.pop_back();

                int idx = c.idx;

                // Remove current value from sum
                if (value[idx] != -1) {
                    total -= value[idx];
                }

                // Restore previous value
                value[idx] = c.oldValue;

                // Add restored value to sum
                if (value[idx] != -1) {
                    total += value[idx];
                }
            }
        }

        else if (s == "K") {
            // Commit current session
            // Changes remain in history so that
            // the parent session can still undo them.
            sessions.pop_back();
        }
    }

    cout << '\n';

    return 0;
}
