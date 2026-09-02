#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> height(n);
    for (int i = 0; i < n; i++) {
        cin >> height[i];
    }

    vector<int> ans(n);
    stack<int> st;

    // Find the nearest strictly taller tower on the right
    for (int i = n - 1; i >= 0; i--) {

        // Remove towers that are not taller than height[i]
        while (!st.empty() && height[st.top()] <= height[i]) {
            st.pop();
        }

        if (st.empty()) {
            // No taller tower to the right
            ans[i] = n - 1 - i;
        } else {
            // Nearest strictly taller tower
            ans[i] = st.top() - i;
        }

        st.push(i);
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }

    cout << '\n';

    return 0;
}
