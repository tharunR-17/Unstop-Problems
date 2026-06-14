#include <bits/stdc++.h>
#include <string>
using namespace std;

void user_logic(int n, string &s) {
    // Write your logic here.
        // Parameters:
            //     n: Length of the string
                //     s: String consisting of lowercase Latin alphabets
                    // Returns:
                        //     Sorted string based on the given conditions

                            map<int, vector<char>>mp;
                                for(int i=0; i<n; i++){
                                        int diff= (s[i]-'a'+1)%5;
                                                mp[diff].push_back(s[i]);
                                                    }

                                                        // string ans="";
                                                            int i=0;
                                                                for(auto it:mp){
                                                                        vector<char> v= it.second;
                                                                                sort(v.begin(), v.end());
                                                                                        reverse(v.begin(), v.end());
                                                                                                for(auto el:v)
                                                                                                            s[i++]=el;
                                                                                                                }
                                                                                                                    

                                                                                                                    }

                                                                                                                    int main() {
                                                                                                                        int n;
                                                                                                                            string s;
                                                                                                                                
                                                                                                                                    cin >> n >> s;
                                                                                                                                        
                                                                                                                                            user_logic(n, s);
                                                                                                                                                
                                                                                                                                                    // Call user logic function and print the output
                                                                                                                                                        cout << s << endl;
                                                                                                                                                            
                                                                                                                                                                return 0;
                                                                                                                                                                }
