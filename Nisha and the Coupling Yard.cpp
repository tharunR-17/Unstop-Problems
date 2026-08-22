#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> weights(n);
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }
    deque<int> min_dq, max_dq;
    
    long long min_imbalance = -1;
    int best_position = -1;

    for (int i = 0; i < n; ++i) {
        if (!min_dq.empty() && min_dq.front() <= i - m) {
            min_dq.pop_front();
        }
        if (!max_dq.empty() && max_dq.front() <= i - m) {
            max_dq.pop_front();
        }

        while (!min_dq.empty() && weights[min_dq.back()] >= weights[i]) {
            min_dq.pop_back();
        }
        while (!max_dq.empty() && weights[max_dq.back()] <= weights[i]) {
            max_dq.pop_back();
        }

        min_dq.push_back(i);
        max_dq.push_back(i);

        if (i >= m - 1) {
            long long current_max = weights[max_dq.front()];
            long long current_min = weights[min_dq.front()];
            long long current_imbalance = current_max - current_min;

            if (min_imbalance == -1 || current_imbalance < min_imbalance) {
                min_imbalance = current_imbalance;
                best_position = (i - m + 1) + 1;
            }
        }
    }

    cout << min_imbalance << " " << best_position << "\n";

    return 0;
}
