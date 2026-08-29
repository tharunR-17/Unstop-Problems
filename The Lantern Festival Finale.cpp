#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long L;

    cin >> n >> L;

    vector<long long> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    deque<int> maxDeque;
    deque<int> minDeque;

    long long sum = 0;
    long long ans = 0;

    int left = 0;

    for (int right = 0; right < n; right++) {

        sum += a[right];

        // Maintain decreasing deque for maximum
        while (!maxDeque.empty() &&
               a[maxDeque.back()] <= a[right]) {
            maxDeque.pop_back();
        }
        maxDeque.push_back(right);

        // Maintain increasing deque for minimum
        while (!minDeque.empty() &&
               a[minDeque.back()] >= a[right]) {
            minDeque.pop_back();
        }
        minDeque.push_back(right);

        // Window is invalid
        while (!maxDeque.empty() && !minDeque.empty() &&
               a[maxDeque.front()] - a[minDeque.front()] > L) {

            if (maxDeque.front() == left) {
                maxDeque.pop_front();
            }

            if (minDeque.front() == left) {
                minDeque.pop_front();
            }

            sum -= a[left];
            left++;
        }

        // Current window is valid
        ans = max(ans, sum);
    }

    cout << ans << '\n';

    return 0;
}
