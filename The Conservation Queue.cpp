#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
public:
    void processEvents(int M) {
        priority_queue<pair<long long, long long>> pq;
        unordered_map<long long, bool> active;

        for (int i = 0; i < M; i++) {
            string type;
            cin >> type;

            if (type == "ARRIVE") {
                long long id, urgency;
                cin >> id >> urgency;

                pq.push({urgency, -id});
                active[id] = true;
            }
            else if (type == "WITHDRAW") {
                long long id;
                cin >> id;

                active[id] = false;
            }
            else if (type == "RESTORE") {
                while (!pq.empty() && !active[-pq.top().second]) {
                    pq.pop();
                }

                if (pq.empty()) {
                    cout << "IDLE\n";
                } else {
                    long long id = -pq.top().second;
                    pq.pop();

                    active[id] = false;
                    cout << id << '\n';
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    Solution sol;
    sol.processEvents(M);

    return 0;
}
