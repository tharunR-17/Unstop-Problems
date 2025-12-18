#include<bits/stdc++.h>
using namespace std;
int n,x,y,r,b,w,s[15],m=-1e9,i;
int main(){
    cin>>n;
    while(cin>>x>>y>>r>>b>>w)s[x]+=r*2+b*3-w*5;
    for(i=1;i<=n;i++)if(s[i]>m)m=s[i],x=i;
    cout<<x<<" "<<m;
}
