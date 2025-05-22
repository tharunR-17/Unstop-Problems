#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=2e5+5;
int n,m;
vector<int> p[N];
ll f[N];
void solve(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid);
	ll v=f[mid];
	for(int i=1;i<=r-l;i++){
		auto it=upper_bound(p[i].begin(),p[i].end(),v%n);
		int t=lower_bound(f+l,f+mid+1,v/n*n+(it==p[i].begin()?p[i].back()-n:*prev(it)))-f;
		if(t+i<=m) f[t+i]=max(f[t+i],v/n*n+(it==p[i].end()?p[i][0]+n:*it));
	}
	solve(mid+1,r);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),p[x].push_back(i);
	solve(0,m);printf("%lld\n",f[m]);
	return 0;
}
