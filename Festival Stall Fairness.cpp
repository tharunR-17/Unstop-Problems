#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
    // Optimize standard input/output streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long d;
    if (!(cin >> n >> d)) return 0;

    vector<long long> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    deque<int> max_deque; // Stores indices, elements in decreasing order
    deque<int> min_deque; // Stores indices, elements in increasing order

    int left = 0;
    int max_length = 0;

    for (int right = 0; right < n; ++right) {
        // Maintain decreasing order in max_deque
        while (!max_deque.empty() && prices[max_deque.back()] <= prices[right]) {
            max_deque.pop_back();
        }
        max_deque.push_back(right);

        // Maintain increasing order in min_deque
        while (!min_deque.empty() && prices[min_deque.back()] >= prices[right]) {
            min_deque.pop_back();
        }
        min_deque.push_back(right);

        // If the current window's max - min exceeds d, shrink from the left
        while (prices[max_deque.front()] - prices[min_deque.front()] > d) {
            if (max_deque.front() == left) {
                max_deque.pop_front();
            }
            if (min_deque.front() == left) {
                min_deque.pop_front();
            }
            left++;
        }

        // Update the maximum length found so far
        max_length = max(max_length, right - left + 1);
    }

    cout << max_length << "\n";

    return 0;
}
