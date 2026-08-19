#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> st;
    st.reserve(n);

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;

        st.push_back(x);

        // Merge repeatedly while the top two are equal
        while (st.size() >= 2 &&
               st[st.size() - 1] == st[st.size() - 2]) {

            long long merged = st.back() + st[st.size() - 2];

            st.pop_back();
            st.pop_back();

            st.push_back(merged);
        }
    }

    cout << st.size() << '\n';

    for (size_t i = 0; i < st.size(); ++i) {
        if (i) cout << ' ';
        cout << st[i];
    }
    cout << '\n';

    return 0;
}
