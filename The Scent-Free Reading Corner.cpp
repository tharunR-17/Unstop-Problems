#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<long long> a(N);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    map<long long, int> freq;

    int left = 0;
    int ans = 0;

    for (int right = 0; right < N; right++) {

        // Add current element
        freq[a[right]]++;

        // More than K distinct values
        while ((int)freq.size() > K) {
            freq[a[left]]--;

            if (freq[a[left]] == 0) {
                freq.erase(a[left]);
            }

            left++;
        }

        // Current window is valid
        ans = max(ans, right - left + 1);
    }

    cout << ans << '\n';

    return 0;
}
