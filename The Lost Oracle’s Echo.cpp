#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// Placeholder for user logic function
vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int user_logic(const string& s) {
    int n = s.length();

    vector<int> z = z_function(s);
    z[0] = n;

    int len = 0;
    for (int k =1 ; k < n; k++) {
        if (z[k] == n-k) {
            len = n-k;
            break;
        }
    }

    if (len == 0) {
        return 0;
    }

    int cnt = 0;
    for (int v : z) {
        if (v >= len) {
            cnt++;
        }
    }

    return cnt;
}

int main() {
    string S;
    cin >> S;

    // Call user logic function and print the output
    int result = user_logic(S);
    cout << result << endl;

    return 0;
}
