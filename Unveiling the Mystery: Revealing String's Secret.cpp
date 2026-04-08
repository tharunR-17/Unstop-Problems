#include <bits/stdc++.h>
using namespace std;

bool checkSubseq(const string &a, const string &b) {
    int p = 0, q = 0;
    while (p < a.size() && q < b.size()) {
        if (a[p] == b[q]) q++;
        p++;
    }
    return q == b.size();
}

int main() {
    string s, t;
    cin >> s >> t;

    string temp = s;
    const int limit = 2000;

    for (int d = 1; d <= limit; ++d) {
        if (checkSubseq(temp, t)) {
            cout << d << endl;
            return 0;
        }
        reverse(temp.begin(), temp.end());
        temp += s;
    }

    cout << -1 << endl;
    return 0;
}
