#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    // Min-heap storing end times of active sessions
    priority_queue<int, vector<int>, greater<int>> pq;

    int denied = 0;

    for (int i = 0; i < M; i++) {
        string id;
        int arrival, duration;
        cin >> id >> arrival >> duration;

        // Free computers that have finished
        while (!pq.empty() && pq.top() <= arrival) {
            pq.pop();
        }

        // Allocate if available
        if ((int)pq.size() < N) {
            pq.push(arrival + duration);
        } else {
            denied++;
        }
    }

    cout << denied << endl;
    return 0;
}
