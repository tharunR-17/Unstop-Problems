#include <bits/stdc++.h>
using namespace std;


signed main() {
    /* Enter your code here. Read input from STDIN. Prlong long output to STDOUT */   

//      #ifndef ONLINE_JUDGE

//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);

// #endif

    long long n;
    cin>>n;

    long long a[n];
    for(long long i=0;i<n;i++)cin>>a[i];

    vector<long long> next(n,n),prev(n,-1);

    stack<long long> s;

    for(long long i=0;i<n;i++){

        if(s.empty()||a[s.top()]<a[i]){
            s.push(i);
        }else{
            while(!s.empty() && a[i]<=a[s.top()]){
                next[s.top()]=i;
                s.pop();
            }
            s.push(i);
        }

    }

    for(long long i=n-1;i>=0;i--){

        if(s.empty()||a[s.top()]<=a[i]){
            s.push(i);
        }else{
            while(!s.empty() && a[i]<a[s.top()]){
                prev[s.top()]=i;
                s.pop();
            }
            s.push(i);
        }

    }

    long long ans=0;

    for(long long i=0;i<n;i++){
        // cout<<prev[i]<<" "<<next[i]<<endl;
        ans+=1ll*a[i]*(i-prev[i])*(next[i]-i);

    }

    cout<<ans%1000000007<<endl;

    return 0;
}
