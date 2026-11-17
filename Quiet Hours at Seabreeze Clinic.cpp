#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Patient {
    int id;
    int severity;
    int arrival;
};

struct Compare {
    bool operator()(const Patient& a, const Patient& b) const {
        if (a.severity != b.severity) {
            return a.severity < b.severity;
        }

        return a.arrival > b.arrival;
    }
};

class Clinic {
private:
    priority_queue<Patient, vector<Patient>, Compare> pq;

    unordered_map<int, int> currentSeverity;
    unordered_map<int, int> arrivalTime;

    int timer = 0;
    int waiting = 0;

public:
    void arrive(int id, int severity) {
        timer++;

        currentSeverity[id] = severity;
        arrivalTime[id] = timer;

        pq.push({id, severity, timer});
        waiting++;
    }

    void report(int id, int severity) {
        if (currentSeverity.find(id) == currentSeverity.end()) {
            return;
        }

        int updated = max(currentSeverity[id], severity);

        if (updated == currentSeverity[id]) {
            return;
        }

        currentSeverity[id] = updated;

        pq.push({id, updated, arrivalTime[id]});
    }

    void leave(int id) {
        auto it = currentSeverity.find(id);

        if (it == currentSeverity.end()) {
            return;
        }

        currentSeverity.erase(it);
        arrivalTime.erase(id);
        waiting--;
    }

    void call() {
        while (!pq.empty()) {
            Patient p = pq.top();

            auto it = currentSeverity.find(p.id);

            if (it == currentSeverity.end() ||
                it->second != p.severity) {
                pq.pop();
                continue;
            }

            pq.pop();

            cout << p.id << '\n';

            currentSeverity.erase(p.id);
            arrivalTime.erase(p.id);

            waiting--;
            return;
        }

        cout << "NONE\n";
    }

    void printWaiting() {
        cout << "Waiting: " << waiting << '\n';
    }
};

void solve() {
    int q;
    cin >> q;

    Clinic clinic;

    for (int i = 0; i < q; i++) {
        string operation;
        cin >> operation;

        if (operation == "ARRIVE") {
            int id, severity;
            cin >> id >> severity;

            clinic.arrive(id, severity);
        }
        else if (operation == "REPORT") {
            int id, severity;
            cin >> id >> severity;

            clinic.report(id, severity);
        }
        else if (operation == "LEAVE") {
            int id;
            cin >> id;

            clinic.leave(id);
        }
        else if (operation == "CALL") {
            clinic.call();
        }
    }

    clinic.printWaiting();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
