#include <bits/stdc++.h>
using namespace std;

bool pos(vector<int>&vec, int k, int K){
    int n=vec.size();
    int ele=vec[0]+k;
    long long cnt = 0;
    for(int i = 0; i < n; i++){
        if(vec[i] > ele){
            cnt += (vec[i] - ele);
            if(cnt > K) return false;
        }
    }
    return true;
}

int main() {
    int n,k;
    cin>>n>>k;
    // cout<<n<<" "<<k;
    vector<int>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    sort(v.begin(),v.end());
    int l=0,r=v[n-1]-v[0];
    int ans=0;

    while(l<=r){
        int mid=(l+r)/2;
        if(pos(v,mid,k)){
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    cout<<ans<<endl;
    
    return 0;
}
