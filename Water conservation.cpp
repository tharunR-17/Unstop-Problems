#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n;
    cin>>n;

    int a[n],l[n],r[n];

    for(int i=0;i<n;i++){
        cin>>a[i];
    }

    l[0]=a[0],r[n-1]=a[n-1];

    for(int i=1;i<n;i++){

        l[i]=max(l[i-1],a[i]);
        r[n-i-1]=max(r[n-i],a[n-i-1]);

    }
    int ans=0;
    for(int i=0;i<n;i++){
        ans+=min(l[i],r[i])-a[i];
    }


cout<<ans<<endl;

    return 0;
}
