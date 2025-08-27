#include<bits/stdc++.h>
using namespace std;

std::string smallest_window(const std::string& s1, const std::string& s2) {
    // Write your logic here.
    // Parameters:
    //     s1: First input string
    //     s2: Second input string
    // Returns:
    //     Smallest window (substring) of s1 that contains any permutation of s2
    int n = s1.size(), m = s2.size(), i=0, j=0, cnt=0;
    vector<int> target(26, 0), cur(26, 0);
    for(char ch : s2){
        target[ch-'a']+=1;
    }

    for(int i=0;i<26;i++){
        if(target[i]>0){
            cnt+=1;
        }
    }
    int ans = n+1;
    string res="";
    while(i<n)
    {
        int ele = s1[i++]-'a';
        cur[ele]+=1;
        if(cur[ele]==target[ele]){
            cnt-=1;
        }else{

        }
        while(cnt==0){
            // cout<<i<<" "<<j<<"\n";
            if(ans>i-j){
                ans = i-j;
                res = s1.substr(j, i-j);
            }
            ele = s1[j++]-'a';
            cur[ele]-=1;
            if(cur[ele]==target[ele]-1)cnt+=1;
        }
    }
    return res;
}

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;

    // Call user logic function and print the output
    std::string result = smallest_window(s1, s2);
    std::cout << result << std::endl;

    return 0;
}
