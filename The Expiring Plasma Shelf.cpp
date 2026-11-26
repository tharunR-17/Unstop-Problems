#include <bits/stdc++.h>
using namespace std;

struct Unit {
    int expiry;
    int id;

    bool operator>(const Unit& other) const {
        if (expiry != other.expiry)
            return expiry > other.expiry;

        return id > other.id;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q, G;
    cin >> q >> G;

    // One min-heap for each blood group
    vector<priority_queue<Unit,
        vector<Unit>,
        greater<Unit>>> pq(G + 1);

    // 1 = available, 0 = unavailable
    unordered_map<int, bool> status;
    status.reserve(q * 2);

    for (int i = 0; i < q; i++) {
        int t;
        char type;
        cin >> t >> type;

        if (type == 'D') {
            int id, group, expiry;
            cin >> id >> group >> expiry;

            pq[group].push({expiry, id});
            status[id] = true;
        }

        else if (type == 'C') {
            int id;
            cin >> id;

            // Withdraw the unit
            if (status.count(id)) {
                status[id] = false;
            }
        }

        else if (type == 'R') {
            int group;
            cin >> group;

            auto &heap = pq[group];

            // Remove withdrawn and expired units
            while (!heap.empty()) {
                Unit current = heap.top();

                if (!status[current.id] ||
                    current.expiry < t) {

                    heap.pop();
                    status[current.id] = false;
                }
                else {
                    break;
                }
            }

            // No usable unit available
            if (heap.empty()) {
                cout << "NONE\n";
            }
            else {
                Unit selected = heap.top();
                heap.pop();

                cout << selected.id << '\n';

                // Mark as handed over
                status[selected.id] = false;
            }
        }
    }

    return 0;
}
