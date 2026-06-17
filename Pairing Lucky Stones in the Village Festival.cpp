#include<bits/stdc++.h>
using namespace std;

int main(){
    int p,n,m;
    cin>>p>>n>>m;
    vector<int>v(p);
    for(int i=0;i<p;i++){
        cin>>v[i];
    }
    int ans=0;
    for(int i=0;i<p-1;i++){
        for(int j=i+1;j<p;j++){
            if((v[i]%n==0 || v[i]%m==0) && (v[j]%n==0 || v[j]%m==0)){
                ans++;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
