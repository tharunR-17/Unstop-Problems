#include "bits/stdc++.h"
using namespace std;

bool inline isVowel(char &ch)
{
    switch(ch)
    {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        return 1;
        default:
        return 0;
    }

    return 0;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin>>n;
    string s;
    cin>>s; 

    stack<char> st;

    for(int i=0;i<n;++i)
    {
        if(!isVowel(s[i]))
        {
            st.push(s[i]);
        }
        else
        {
            
            if(st.empty() || (!isVowel(st.top()) && st.top()!='$') ) 
            {
                st.push(s[i]);
            }     
            else if(isVowel(st.top()))
            {
                st.push(s[i]);
                st.push('$');
            }
            else
            {
                st.pop();
                st.push(s[i]);
            }
        }
    }

    if(st.size()>3 && st.top()=='$')
    {
        st.pop();
        char q=st.top();
        st.pop();
        char p=st.top();
        st.pop();
        char m=st.top();
        st.push(p);
        st.push(q);
        if(!isVowel(m))
        {
            st.push('$');
        }
    }

    string ans;

    while(!st.empty())
    {
        char topEle=st.top();
        ans.push_back(topEle);
        st.pop();
    }

    for(int i=ans.length()-1;i>=0;--i)
    {
        cout<<ans[i];
    }

    return 0;
}
