#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<ll> A(N);
    vector<ll> pref(N + 1, 0);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        pref[i + 1] = pref[i] + A[i];
    }

    // Find the range [L[i], R[i]] where A[i] is the maximum
    // L[i]: the nearest index to the left where A[j] > A[i]
    // R[i]: the nearest index to the right where A[j] >= A[i]
    vector<int> L(N), R(N);
    vector<int> s;

    for (int i = 0; i < N; i++) {
        while (!s.empty() && A[s.back()] <= A[i]) s.pop_back();
        L[i] = s.empty() ? 0 : s.back() + 1;
        s.push_back(i);
    }
    s.clear();
    for (int i = N - 1; i >= 0; i--) {
        while (!s.empty() && A[s.back()] < A[i]) s.pop_back();
        R[i] = s.empty() ? N - 1 : s.back() - 1;
        s.push_back(i);
    }

    ll count = 0;
    for (int i = 0; i < N; i++) {
        int left_len = i - L[i];
        int right_len = R[i] - i;

        // Small-to-large heuristic: iterate over the smaller side
        if (left_len < right_len) {
            for (int l = L[i]; l <= i; l++) {
                // Condition: 2 * A[i] > pref[r+1] - pref[l]
                // pref[r+1] < 2 * A[i] + pref[l]
                ll threshold = 2 * A[i] + pref[l];
                
                // We need r such that i <= r <= R[i]
                // Find the largest r such that pref[r+1] < threshold
                auto it = lower_bound(pref.begin() + i + 1, pref.begin() + R[i] + 2, threshold);
                int r_limit = (int)(distance(pref.begin(), it)) - 2;
                
                if (r_limit >= i) {
                    count += (r_limit - i + 1);
                    // Subtract the case where l == r, as length must be >= 2
                    if (l == i) count--; 
                }
            }
        } else {
            for (int r = i; r <= R[i]; r++) {
                // pref[l] > pref[r+1] - 2 * A[i]
                ll threshold = pref[r + 1] - 2 * A[i];
                
                // Find the smallest l such that pref[l] > threshold
                auto it = upper_bound(pref.begin() + L[i], pref.begin() + i + 1, threshold);
                int l_limit = (int)(distance(pref.begin(), it));
                
                if (l_limit <= i) {
                    count += (i - l_limit + 1);
                    if (r == i) count--;
                }
            }
        }
    }

    cout << count << endl;

    return 0;
}
