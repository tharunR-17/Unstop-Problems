#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF=1e18;
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,m,k;
    cin>>n>>m>>k;
    vector<vector<pair<int,int>>>adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<vector<ll>>dist(n,vector<ll>(k+1,INF));
    priority_queue<tuple<ll,int,int>,vector<tuple<ll,int,int>>,greater<>>pq;
    dist[0][0]=0;
    pq.push({0,0,0});
    while(!pq.empty()){
        auto [d,u,used]=pq.top();
        pq.pop();
        if(d>dist[u][used])continue;
        for(auto [v,w]:adj[u]){
            ll cost=w;
            for(int j=0;j+used<=k;j++){
                if(j>0) cost/=2;
                if(dist[v][used+j]>d+cost){
                    dist[v][used+j]=d+cost;
                    pq.push({dist[v][used+j],v,used+j});
                }
                if(cost==0) break;
            }
        }
    }
    ll ans=INF;
    for(int j=0;j<=k;j++){
        ans=min(ans,dist[n-1][j]);
    }
    cout<<ans;
}
