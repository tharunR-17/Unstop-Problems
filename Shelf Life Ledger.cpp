#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Batch {
    long long expiry;
    long long id;
    long long quantity;

    bool operator>(const Batch& other) const {
        return expiry > other.expiry;
    }
};

struct BatchInfo {
    long long expiry;
    long long remaining;
    bool active;
};

void solve(int N, long long Z) {
    priority_queue<Batch, vector<Batch>, greater<Batch>> pq;
    unordered_map<long long, BatchInfo> batches;

    long long expired = 0;
    long long recalled = 0;

    for (int i = 0; i < N; i++) {
        long long day;
        char type;
        cin >> day >> type;

        // Expire batches before processing today's entry
        while (!pq.empty() && pq.top().expiry < day) {
            Batch b = pq.top();
            pq.pop();

            auto it = batches.find(b.id);
            if (it != batches.end() && it->second.active) {
                expired += it->second.remaining;
                it->second.remaining = 0;
                it->second.active = false;
            }
        }

        if (type == 'R') {
            long long id, expiry, quantity;
            cin >> id >> expiry >> quantity;

            batches[id] = {expiry, quantity, true};
            pq.push({expiry, id, quantity});
        }
        else if (type == 'D') {
            long long demand;
            cin >> demand;

            long long supplied = 0;

            while (demand > 0 && !pq.empty()) {
                Batch b = pq.top();
                pq.pop();

                auto it = batches.find(b.id);

                if (it == batches.end() || !it->second.active ||
                    it->second.remaining == 0) {
                    continue;
                }

                long long used = min(demand, it->second.remaining);

                demand -= used;
                supplied += used;
                it->second.remaining -= used;

                if (it->second.remaining > 0) {
                    pq.push({it->second.expiry, b.id,
                             it->second.remaining});
                } else {
                    it->second.active = false;
                }
            }

            cout << supplied << '\n';
        }
        else if (type == 'C') {
            long long id;
            cin >> id;

            auto it = batches.find(id);

            if (it != batches.end() && it->second.active) {
                recalled += it->second.remaining;
                it->second.remaining = 0;
                it->second.active = false;
            }
        }
    }

    // Final audit
    while (!pq.empty()) {
        Batch b = pq.top();
        pq.pop();

        auto it = batches.find(b.id);

        if (it != batches.end() && it->second.active &&
            it->second.expiry < Z) {
            expired += it->second.remaining;
            it->second.remaining = 0;
            it->second.active = false;
        }
    }

    cout << "EXPIRED " << expired
         << " RECALLED " << recalled << '\n';
}

int main() {
    int N;
    long long Z;
    cin >> N >> Z;

    solve(N, Z);

    return 0;
}
