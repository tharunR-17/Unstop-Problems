#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

int main() {
    int n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // prefix sum for faster range sum calculation
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i)
        prefix[i + 1] = prefix[i] + a[i];

    // max heap to store subarray sums
    priority_queue<ll> maxHeap;

    // generate all subarray sums in O(N^2)
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ll sum = prefix[j] - prefix[i];
            maxHeap.push(sum);
        }
    }

    // get top K maximum subarray sums
    ll ans = 0;
    for (int i = 0; i < k && !maxHeap.empty(); ++i) {
        ans += maxHeap.top();
        maxHeap.pop();
    }

    cout << ans << endl;
    return 0;
}
