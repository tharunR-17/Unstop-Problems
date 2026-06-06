#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

string decodeMsg(string s) {

    string ans = "";
    int i = s.length() - 1;
    string temp = "";
    while(i >= 0) {

        if(s[i] == '#') {
            temp = s[i-1];
            temp = s[i-2] + temp;
            int k = stoi(temp);
            ans = char(k - 1 + 'a') + ans;
            temp = "";
            i -= 3;
        } else {

            temp = s[i];
            int k = stoi(temp);
            i--;
            temp = "";
            ans = char(k - 1 + 'a') + ans;

        }
    }
    return ans;
}

int main() {
    
    string s;
    cin>>s;
    string ans = decodeMsg(s);
    cout<<ans<<endl; 
    return 0;
}
