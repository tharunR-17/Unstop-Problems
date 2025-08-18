#include <bits/stdc++.h>
using namespace std;

// User logic function
string canMakeHalvesEqual(const string& S) {
    // Write your logic here

    int n=S.size();
    string s1=S.substr(0, n/2);
    string s2=S.substr(n/2, n/2);

    int zero1=0, one1=0;
    int zero2=0, one2=0;
    for (auto it: s1){
        if (it=='0'){
            zero1++;
        }
        else{
            one1++;
        }
    }

    for (auto it: s2){
        if (it=='0'){
            zero2++;
        }
        else{
            one2++;
        }
    }
    
    string ans;
    if (zero1==zero2 && one1==one2){
        ans="YES";
    }
    else{
        ans="NO";
    }

    return ans; // Placeholder return
}

int main() {
    string S;
    cin >> S;

    // Call the user logic function and print the result
    string result = canMakeHalvesEqual(S);
    cout << result << endl;

    return 0;
}
