#include <bits/stdc++.h>
using namespace std;


signed main() {
    /* Enter your code here. Read input from STDIN. Prlong long output to STDOUT */   

    long long n;
    cin>>n;

    long long ans=0;

    for(long long i=1;i*i<=3*n;i++){

        long long y=n-(i*(i-1))/2;
        if(y<=0)break;

        if(y%i==0){

            ans++;

        }

    }

    cout<<ans<<endl;

    return 0;
}
