#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        unordered_set<int> seen;
        bool duplicate = false;

        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;

            if (seen.count(x))
                duplicate = true;
            else
                seen.insert(x);
        }

        cout << (duplicate ? "YES" : "NO") << '\n';
    }

    return 0;
}
