#include<bits/stdc++.h>
using namespace std;
int main() {
 long long n;
  cin>>n;
   vector<long long int>v(n);
    for(int i=0;i<n;i++)
     cin>>v[i];
      long long int mx=0;
        for(int i=0;i<n;i++)
          {
             mx=max(mx,v[i]);
                cout<<v[i]+mx<<" ";
                  }
                  }
