#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
    ll n, k; cin>>n>>k;
    ll a[n], b[n];
    for(ll i=0; i<n; i++) cin>>a[i]>>b[i];
    ll count = 0;
    for(ll i=0; i<n; i++) {
        if(a[i] <= k || b[i] <= k) count++;
    }
    cout<<count<<endl;

    return 0;

}
