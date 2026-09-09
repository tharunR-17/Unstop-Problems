#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long D;

    cin >> N >> D;

    vector<long long> a(N);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    unordered_set<long long> seen;
    multiset<long long> values;

    int left = 0;

    int bestLength = 0;
    int bestStart = 0;

    for (int right = 0; right < N; right++) {

        // Remove duplicate
        while (seen.count(a[right])) {
            seen.erase(a[left]);
            values.erase(values.find(a[left]));
            left++;
        }

        // Add current element
        seen.insert(a[right]);
        values.insert(a[right]);

        // Fix the max-min condition
        while (!values.empty() &&
               *values.rbegin() - *values.begin() > D) {

            seen.erase(a[left]);
            values.erase(values.find(a[left]));
            left++;
        }

        int length = right - left + 1;

        if (length > bestLength) {
            bestLength = length;
            bestStart = left;
        }
    }

    // Convert 0-indexed start to 1-indexed
    cout << bestLength << " " << bestStart + 1 << '\n';

    return 0;
}
