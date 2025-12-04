#include "bits/stdc++.h"
using namespace std;

// User-defined function to be implemented
int min_operations_to_maximize(int n, string s) {
    // The user will write the main logic here
    int ans=0;
    int count=0;
    for(int i=n-1;i>=0;--i)
    {
        if(s[i]=='1')
        {
            ++count;
        }
        else
        {
            ans+=count;
        }
    }

    return ans;
}

int main() {
    int n;
    string s;
    cin >> n;
    cin >> s;

    int result = min_operations_to_maximize(n, s);
    cout << result << endl;

    return 0;
}
