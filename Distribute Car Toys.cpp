#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int k,s;
    cin>>k>>s;
    int ans=0;
    for(int i=0;i<=min(s,k);i++){
        for(int j=0;j<=min(s-i,k);j++){
            int l=s-i-j;
            if(l>=0 && l<=k)ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
