#include <bits/stdc++.h>
#include <string>
using namespace std;

pair<string, int> find_min_substring_with_swaps(const string &s, int k) {
    // Write your logic here.
    unordered_map<char,int>mp;
    for(auto i:s)mp[i]++;
    int oo=0;
    for(auto [a,b]:mp){
        if(b%2!=0)oo++;
    }
    if(oo>=2)return {"No",0};
    else return {"Yes",0};
}

int main() {
    string s;
    int k;
    cin >> s >> k;
    
    auto result = find_min_substring_with_swaps(s, k);
    cout << result.first << endl;
    // cout << result.second << endl;
    
    return 0;
}
