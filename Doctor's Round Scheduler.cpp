#include <iostream>
#include <vector>
using namespace std;

struct Patient {
    int id;
    int priority;
    int time;
    // Constructor
    Patient(int id, int priority, int time) : id(id), priority(priority), time(time) {}
};

#include <algorithm>

vector<int> determineVisitOrder(vector<Patient>& patients) {
    // Sort using custom comparator
    sort(patients.begin(), patients.end(), [](const Patient& a, const Patient& b) {
        if (a.priority != b.priority)
            return a.priority > b.priority;   // higher priority first
        if (a.time != b.time)
            return a.time < b.time;           // lower time first
        return a.id < b.id;                   // lower ID first
    });

    // Extract sorted IDs
    vector<int> order;
    for (const auto& p : patients) {
        order.push_back(p.id);
    }

    return order;
}

int main() {
    int N;
    cin >> N;

    vector<Patient> patients;
    for (int i = 0; i < N; ++i) {
        int id, priority, time;
        cin >> id >> priority >> time;
        patients.emplace_back(id, priority, time);
    }

    // Call user logic function
    vector<int> visitOrder = determineVisitOrder(patients);

    // Output the result
    for (int id : visitOrder) {
        cout << id << " ";
    }
    cout << endl;

    return 0;
}
