#include <bits/stdc++.h>
using namespace std;



  long long ans(int x,long long int y,int m){
      if(y==0) return 1;
  
      long long int temp=ans(x,y/2,m);
      temp*=temp;
      temp%=m;
      if(y%2) temp*=x;
      temp%=m;
      return temp;
  }
    
int main() 
{
    long long int n;;
    cin>>n;
    
    
        long long int m=1000000007;
        long long int o=n/2;
        long long int e=n/2+n%2;
    if(n==0) cout<<0;
    else cout<<(ans(4,o,m)%m*ans(5,e,m)%m)%m;
}
