#include<bits/stdc++.h>
using namespace std;
int n,m,d,t,i,j,k,dp[11][11][22],ans;
string g[11],s;
int main(){
    cin>>n>>m>>d>>t;
    for(i=0;i<n;i++)cin>>g[i];
    cin>>s;
    for(i=0;i<n;i++)for(j=0;j<m;j++){
        int st=i+j,sh=st/t,df=g[i][(j-sh%m+m)%m]!=s[st];
        if(!st){if(df<=d)dp[0][0][df]=1;continue;}
        for(k=df;k<=d;k++){
            if(i)dp[i][j][k]+=dp[i-1][j][k-df];
            if(j)dp[i][j][k]+=dp[i][j-1][k-df];
        }
    }
    for(k=0;k<=d;k++)ans+=dp[n-1][m-1][k];
    cout<<ans;
}
