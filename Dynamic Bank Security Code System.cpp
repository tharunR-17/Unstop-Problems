#include<bits/stdc++.h>
#define ll long long int 
using namespace std;

int main() {
    ll n; cin>>n;
    ll count = 0, maximum = INT_MIN;
    for(ll i=0; i<n; i++) {
        string s; cin>>s;
        ll x = s.length();
        ll sum = 0;
        for(ll i=0; i<x; i++) {
            if((s[i] - '0') % 2 == 0) {
                sum += ((i+1)*(s[i] - '0'));
            } else {
                sum -= ((i+1)*(s[i] - '0'));
            }
        }
        sum = abs(sum);
        if(sum > maximum) {
            maximum = sum;
            count = i + 1;
        }
    }
    cout<<count<<" "<<maximum<<endl;
    return 0;
}
