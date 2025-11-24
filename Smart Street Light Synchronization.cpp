#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    string s;
    cin >> s;
    long long diff0 = 0, diff1 = 0; // diff0: target starts with '0', diff1: starts with '1'
    for (int i = 0; i < N; ++i) {
        char t0 = (i % 2 == 0) ? '0' : '1';
        char t1 = (i % 2 == 0) ? '1' : '0';
        if (s[i] != t0) ++diff0;
        if (s[i] != t1) ++diff1;
    }
    cout << min(diff0, diff1) << '\n';
    return 0;
}
