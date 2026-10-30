#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    const int MAX_ID = 200000;

    set<pair<int, int>> parcels;
    vector<int> deadline(MAX_ID + 1, -1);

    while (Q--) {
        string op;
        cin >> op;

        if (op == "ARRIVE") {
            int id, d;
            cin >> id >> d;

            deadline[id] = d;
            parcels.insert({d, id});
        }
        else if (op == "DELAY") {
            int id, d;
            cin >> id >> d;

            parcels.erase({deadline[id], id});
            deadline[id] = d;
            parcels.insert({d, id});
        }
        else if (op == "CANCEL") {
            int id;
            cin >> id;

            parcels.erase({deadline[id], id});
            deadline[id] = -1;
        }
        else if (op == "DISPATCH") {
            if (parcels.empty()) {
                cout << "IDLE\n";
            } else {
                auto it = parcels.begin();
                int id = it->second;

                cout << id << '\n';

                parcels.erase(it);
                deadline[id] = -1;
            }
        }
    }

    return 0;
}
