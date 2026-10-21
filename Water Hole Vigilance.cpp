#include <iostream>
#include <vector>
#include <map>
#include <deque>

using namespace std;

int main() {
    // Optimize standard I/O operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long W, K;
    if (!(cin >> N >> W >> K)) return 0;

    // Map to store a deque of timestamps for each species code
    map<long long, deque<long long>> species_queues;

    int alert_count = 0;
    long long earliest_T = -1;
    long long earliest_S = -1;

    for (int i = 0; i < N; ++i) {
        long long T, S;
        cin >> T >> S;

        long long window_start = T - W;
        auto& dq = species_queues[S];

        // Remove elements that are older than the current window start
        while (!dq.empty() && dq.front() < window_start) {
            dq.pop_front();
        }

        // Add the current record's timestamp
        dq.push_back(T);

        // Check if the species count in the window reaches or exceeds K
        if ((long long)dq.size() >= K) {
            alert_count++;
            if (alert_count == 1) {
                earliest_T = T;
                earliest_S = S;
            }
        }
    }

    // Output results
    cout << alert_count << "\n";
    if (alert_count > 0) {
        cout << earliest_T << " " << earliest_S << "\n";
    } else {
        cout << "QUIET\n";
    }

    return 0;
}
