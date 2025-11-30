#include <bits/stdc++.h>
using namespace std;

int totalTravelTime(int N, vector<int>& G, vector<int>& R, vector<int>& T) {
    int time = 0;
    for (int i = 0; i < N - 1; i++) {
        int green = G[i];
        int red = R[i];
        int cycle = green + red;

        int time_in_cycle = time % cycle;
        if (time_in_cycle < green) {
            time += T[i];
        } else {
            int wait_time = cycle - time_in_cycle;
            time += wait_time + T[i];
        }
    }
    return time;
}

int main() {
    int N;
    cin >> N;

    vector<int> G(N);
    vector<int> R(N);
    vector<int> T(N - 1);

    for (int i = 0; i < N; i++) {
        cin >> G[i];
    }

    for (int i = 0; i < N; i++) {
        cin >> R[i];
    }

    for (int i = 0; i < N - 1; i++) {
        cin >> T[i];
    }

    int result = totalTravelTime(N, G, R, T);
    cout << result << endl;

    return 0;
}
