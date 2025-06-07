#include<bits/stdc++.h>
using namespace std;

void rec(int i, int j, vector<vector<int>>&v, vector<vector<int>>&vis){
    vis[i][j]=1;
    if(i-1>=0 && vis[i-1][j]==0){
        rec(i-1,j,v,vis);
    }
    if(j-1>=0 && vis[i][j-1]==0){
        rec(i,j-1,v,vis);
    }
    if(i+1<v.size() && vis[i+1][j]==0) rec(i+1,j,v,vis);
    if(j+1<v[0].size() && vis[i][j+1]==0) rec(i,j+1,v,vis);
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>v(n,vector<int>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>v[i][j];
        }

    }
    vector<vector<int>>vis(n,vector<int>(m,0));
    rec(0,0,v,vis);
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(vis[i][j] && v[i][j]!=-1)ans+=v[i][j];
        }
    }
    cout<<ans<<endl;

}
