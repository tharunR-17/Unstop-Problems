#include <iostream>
#include <vector>
using namespace std;

void userLogic(int N, int T, vector<pair<int, vector<pair<int, int>>>> &roomData) {
    for (int i = 0; i < N; ++i) {
        int E = roomData[i].first;
        vector<pair<int, int>> intervals = roomData[i].second;

        vector<int> schedule(T, 0);
        int required_hours = 0;

        // Mark required hours as ON (Eco mode = 1)
        for (auto &interval : intervals) {
            int L = interval.first, R = interval.second;
            for (int h = L - 1; h < R; ++h) {
                if (schedule[h] == 0) {
                    schedule[h] = 1;
                    required_hours++;
                }
            }
        }

        // Check energy constraint
        if (required_hours > E) {
            cout << "NOT POSSIBLE" << endl;
        } else {
            for (int j = 0; j < T; ++j) {
                cout << schedule[j];
                if (j != T - 1) cout << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int N, T;
    cin >> N >> T;

    vector<pair<int, vector<pair<int, int>>>> roomData(N);
    for (int i = 0; i < N; ++i) {
        int K, E;
        cin >> K >> E;
        vector<pair<int, int>> intervals(K);
        for (int j = 0; j < K; ++j) {
            int L, R;
            cin >> L >> R;
            intervals[j] = make_pair(L, R);
        }
        roomData[i] = make_pair(E, intervals);
    }

    userLogic(N, T, roomData);

    return 0;
}
