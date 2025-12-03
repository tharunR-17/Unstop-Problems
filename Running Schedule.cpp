#include <bits/stdc++.h>
using namespace std;
int main() {
int n;
cin>>n;
int a[n],sum=0;
for(int i=0;i<n;++i)
{
  cin>>a[i];
  sum+=a[i];
}
int i=0,s=0;
while(2*s<sum)
{
  s+=a[i];
  i++;
}
cout<<i;
return 0;
}
