#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long L;

    cin >> n >> L;

    vector<long long> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    deque<int> maxDeque;
    deque<int> minDeque;

    int left = 0;
    int ans = 0;

    for (int right = 0; right < n; right++) {

        // Maintain decreasing order for maximum
        while (!maxDeque.empty() &&
               a[maxDeque.back()] <= a[right]) {
            maxDeque.pop_back();
        }

        maxDeque.push_back(right);

        // Maintain increasing order for minimum
        while (!minDeque.empty() &&
               a[minDeque.back()] >= a[right]) {
            minDeque.pop_back();
        }

        minDeque.push_back(right);

        // Shrink window until it becomes valid
        while (a[maxDeque.front()] - a[minDeque.front()] > L) {

            if (maxDeque.front() == left) {
                maxDeque.pop_front();
            }

            if (minDeque.front() == left) {
                minDeque.pop_front();
            }

            left++;
        }

        ans = max(ans, right - left + 1);
    }

    cout << ans << '\n';

    return 0;
}
