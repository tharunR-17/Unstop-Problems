#include <bits/stdc++.h>
using namespace std;

int main() {
    // Optimize standard I/O operations for speed
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    long long D;
    if (!(cin >> N >> D >> M)) return 0;

    vector<int> s(N);
    vector<long long> w(N);
    for (int i = 0; i < N; i++) {
        cin >> s[i] >> w[i];
    }

    // Array to store the frequency of species codes in the current window
    // Since species codes are up to 1,000,000, an array of size 1,000,005 is safe.
    vector<int> freq(1000005, 0);
    
    // Monotonic deques to track max and min weights in the window
    deque<int> max_dq, min_dq;

    int L = 0;
    int max_len = 0;
    int best_start = 1;

    for (int R = 0; R < N; R++) {
        // Maintain the minimum deque
        while (!min_dq.empty() && w[min_dq.back()] >= w[R]) {
            min_dq.pop_back();
        }
        min_dq.push_back(R);

        // Maintain the maximum deque
        while (!max_dq.empty() && w[max_dq.back()] <= w[R]) {
            max_dq.pop_back();
        }
        max_dq.push_back(R);

        // Increment the count of the current species
        freq[s[R]]++;

        // If the weight spread exceeds D OR the current species exceeds M
        // shrink the window from the left.
        while (w[max_dq.front()] - w[min_dq.front()] > D || freq[s[R]] > M) {
            freq[s[L]]--;
            
            // Remove the elements from deques if they slip out of the window
            if (max_dq.front() == L) max_dq.pop_front();
            if (min_dq.front() == L) min_dq.pop_front();
            
            L++;
        }

        // Record the answer if the current valid window is the longest found so far.
        // It strictly uses ">" ensuring that earlier windows of the same length 
        // are preferred.
        int curr_len = R - L + 1;
        if (curr_len > max_len) {
            max_len = curr_len;
            best_start = L + 1; // 1-based day index
        }
    }

    cout << max_len << " " << best_start << "\n";

    return 0;
}
