#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> weight(N);
    vector<long long> dest(N);

    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> dest[i];
    }

    // Stack stores {weight, index}
    stack<pair<long long, int>> st;

    // Destination -> total wait gap
    unordered_map<long long, long long> total;

    // Destinations in first appearance order
    vector<long long> order;
    unordered_set<long long> seen;

    for (int i = 0; i < N; i++) {
        if (!seen.count(dest[i])) {
            seen.insert(dest[i]);
            order.push_back(dest[i]);
            total[dest[i]] = 0;
        }
    }

    // Find nearest strictly heavier wagon ahead
    for (int i = N - 1; i >= 0; i--) {

        // Equal or lighter wagons cannot be the answer
        while (!st.empty() && st.top().first <= weight[i]) {
            st.pop();
        }

        long long gap = 0;

        if (!st.empty()) {
            gap = st.top().second - i;
        }

        total[dest[i]] += gap;

        st.push({weight[i], i});
    }

    // Print in first-appearance order
    for (long long d : order) {
        cout << d << " " << total[d] << '\n';
    }

    return 0;
}
