#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int countHomogeneousSubstrings(string s) {
    long long answer = 0;
    int n = s.length();
    long long count = 1;
    char ch = s[0];

    for (int i = 1; i < n; i++) {
        if (ch == s[i]) {
            count++;
        } else {
            ch = s[i];
            answer = (answer + ((count % MOD) * ((count + 1) % MOD) / 2) % MOD) % MOD;
            count = 1;
        }
    }
    answer = (answer + ((count % MOD) * ((count + 1) % MOD) / 2) % MOD) % MOD;
    return answer;
}

int main() {
    string str;
    cin >> str;
    cout << countHomogeneousSubstrings(str) << endl;
    return 0;
}
