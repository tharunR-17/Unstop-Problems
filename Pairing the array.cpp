#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    map<int,int> mp;

    int k,n;
    cin>>k>>n;
long long ans=0;
    int a[n];


    for(int i=0;i<n;i++){
        cin>>a[i];
        int gc=__gcd(k,a[i]);
        int x=k/gc;
        for(auto it:mp){

            if(it.first%x==0)ans+=it.second;

        }

        mp[gc]++;
    }

    cout<<ans<<endl;

    return 0;
}
