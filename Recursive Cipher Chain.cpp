#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindrome(const string &s) {
    int l = 0, r = s.length() - 1;
    while (l < r) {
        if (s[l++] != s[r--]) {
            return false;
        }
    }
    return true;
}

string transform(string s, int K) {
    int n = s.length();
    for (int step = 0; step < K; step++) {
        for (int i = 0; i < n; i++) {
            int offset = (s[i] - 'a' + i * i) % 26;
            s[i] = 'a' + offset;
        }
    }

    if (isPalindrome(s)) {
        return "MAGICAL";
    }

    string minSub = s.substr(0, 3);
    for (int i = 1; i <= n - 3; i++) {
        string current = s.substr(i, 3);
        if (current < minSub) {
            minSub = current;
        }
    }

    return minSub;
}

int main() {
    string S;
    int K;

    getline(cin, S);
    cin >> K;

    cout << transform(S, K) << endl;

    return 0;
}
