#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string s;
    cin >> s;
    int n = s.length();
    unordered_map<string, int> mapp;
    set<pair<int, string>> st;
    for(int i = 0; i + 10 < n; i++) {
        string cur = "";
        for(int j = i; j < i + 10; j++) {
            cur += s[j];
        }
        st.insert({i, cur});
        // cerr << cur << "\n";
        mapp[cur]++;
    }
    for(auto &str : st) {
        // cerr << str << "\n";
        if(mapp[str.second] > 1) {
            cout << str.second << " ";
            mapp[str.second] = 0;
        }
    }
    return 0;
}
