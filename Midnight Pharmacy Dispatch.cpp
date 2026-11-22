#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>

using namespace std;

const int MAX_ID = 200005;
const int MAX_WARD = 100005;

int req_ward[MAX_ID];
int req_urg[MAX_ID];
bool active[MAX_ID];
priority_queue<pair<int, int>> pq[MAX_WARD];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (!(cin >> q)) return 0;

    string cmd;
    while (q--) {
        cin >> cmd;
        if (cmd == "NEW") {
            int id, ward, urg;
            cin >> id >> ward >> urg;
            req_ward[id] = ward;
            req_urg[id] = urg;
            active[id] = true;
            pq[ward].push({urg, -id});
        } else if (cmd == "CHANGE") {
            int id, urg;
            cin >> id >> urg;
            req_urg[id] = urg;
            pq[req_ward[id]].push({urg, -id});
        } else if (cmd == "WITHDRAW") {
            int id;
            cin >> id;
            active[id] = false;
        } else if (cmd == "SERVE") {
            int ward;
            cin >> ward;
            bool served = false;
            while (!pq[ward].empty()) {
                auto [urg, neg_id] = pq[ward].top();
                pq[ward].pop();
                int id = -neg_id;
                if (active[id] && req_urg[id] == urg) {
                    active[id] = false;
                    cout << id << ' ' << urg << '\n';
                    served = true;
                    break;
                }
            }
            if (!served) {
                cout << "NONE\n";
            }
        }
    }

    return 0;
}
