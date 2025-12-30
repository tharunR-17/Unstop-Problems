#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,k,t[N],ans;
vector<int>g[N];
void f(int u,int p){for(int v:g[u])if(v!=p)ans+=1+(abs(t[u]-t[v])>k),f(v,u);}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>k;
    for(int i=1;i<=n;cin>>t[i++]);
    for(int i=1,u,v;i<n;cin>>u>>v,g[u].push_back(v),g[v].push_back(u),i++);
    f(1,0),cout<<ans;
}
