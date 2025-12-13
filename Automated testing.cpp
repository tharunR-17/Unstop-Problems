#include <iostream>
#include <vector>
#include <string>
#include<bits/stdc++.h>
using namespace std;
int user_logic(int n, int x, const std::string& s) {
    // Write your logic here.
    // Parameters:
    //     n (int): Length of the string
    //     x (int): Initial position
    //     s (string): String representing the robot's movements
    // Returns:
    //     int: Number of distinct points visited by the robot
    unordered_set<int> st;
    st.insert(x);
    for(int i=0; i<s.length(); i++){
        if(s[i]=='R'){
            x++;
        }else{
            x--;
        }
        st.insert(x);
    }
    return st.size();
}

int main() {
    int T;
    std::cin >> T;
    
    std::vector<int> results;
    for (int t = 0; t < T; ++t) {
        int n, x;
        std::string s;
        std::cin >> n >> x >> s;
        int result = user_logic(n, x, s);
        results.push_back(result);
    }
    
    for (int result : results) {
        std::cout << result << std::endl;
    }
    
    return 0;
}
