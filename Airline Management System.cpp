#include <iostream>
#include <deque>
#include <unordered_set>
#include <vector>
#include <string>
using namespace std;

void process_boarding(int N, int Q, const vector<pair<int, int>>& events) {
    deque<int> waitingQueue;
    unordered_set<int> boardedSet;
    unordered_set<int> waitingNotBoardedSet;
    int currentID = 1;
    vector<int> results;

    for (const auto& event : events) {
        if (event.first == 1) {
            waitingQueue.push_back(currentID);
            waitingNotBoardedSet.insert(currentID);
            currentID++;
        } else if (event.first == 2) {
            int personID = event.second;
            if (waitingNotBoardedSet.count(personID)) {
                waitingNotBoardedSet.erase(personID);
            }
            boardedSet.insert(personID);
        } else if (event.first == 3) {
            while (!waitingQueue.empty()) {
                int frontPerson = waitingQueue.front();
                if (boardedSet.count(frontPerson)) {
                    waitingQueue.pop_front();
                } else {
                    results.push_back(frontPerson);
                    break;
                }
            }
        }
    }

    for (int result : results) {
        cout << result << endl;
    }
}

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<pair<int, int>> events(Q);

    for (int i = 0; i < Q; ++i) {
        int eventType;
        cin >> eventType;
        if (eventType == 1 || eventType == 3) {
            events[i] = {eventType, 0};
        } else if (eventType == 2) {
            int personID;
            cin >> personID;
            events[i] = {eventType, personID};
        }
    }

    process_boarding(N, Q, events);
    return 0;
}
