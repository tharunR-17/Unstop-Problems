#include <bits/stdc++.h>
using namespace std;

struct Request {
    long long priority;
    long long order;
    long long id;
};

// Higher priority first.
// If priority is equal, smaller order (earlier arrival) first.
struct Compare {
    bool operator()(const Request& a, const Request& b) const {
        if (a.priority != b.priority)
            return a.priority > b.priority;

        return a.order < b.order;
    }
};

struct Info {
    long long priority;
    long long order;
    bool pending;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    set<Request, Compare> pending;
    unordered_map<long long, Info> requests;

    long long order = 0;

    while (q--) {
        string op;
        cin >> op;

        if (op == "ADD") {
            long long id, priority;
            cin >> id >> priority;

            order++;

            requests[id] = {priority, order, true};

            pending.insert({priority, order, id});
        }

        else if (op == "UPDATE") {
            long long id, newPriority;
            cin >> id >> newPriority;

            auto it = requests.find(id);

            // Ignore if request doesn't exist or is no longer pending.
            if (it == requests.end() || !it->second.pending)
                continue;

            // Remove old version.
            pending.erase({
                it->second.priority,
                it->second.order,
                id
            });

            // Update priority but preserve arrival order.
            it->second.priority = newPriority;

            pending.insert({
                newPriority,
                it->second.order,
                id
            });
        }

        else if (op == "CANCEL") {
            long long id;
            cin >> id;

            auto it = requests.find(id);

            // Ignore if request doesn't exist or was already served/cancelled.
            if (it == requests.end() || !it->second.pending)
                continue;

            pending.erase({
                it->second.priority,
                it->second.order,
                id
            });

            it->second.pending = false;
        }

        else if (op == "DISPATCH") {
            if (pending.empty()) {
                cout << -1 << '\n';
                continue;
            }

            // First element = highest priority,
            // earliest arrival in case of tie.
            auto it = pending.begin();

            long long id = it->id;

            cout << id << '\n';

            // Mark as served.
            requests[id].pending = false;

            pending.erase(it);
        }
    }

    return 0;
}
