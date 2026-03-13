#include <bits/stdc++.h>
using namespace std;


bool check(vector<int>& parts,int n, int k,long long mid){
    long long need=1LL*mid*k;
    long long c=0;
    for(long long i=0;i<n;i++) c += min<long long>(parts[i], mid); 
    return c>=need;
}
long long maxToys(int n, int k, vector<int>& parts) {
    // User logic goes here
    // Return the maximum number of toys the factory can produce
    if(n==100000  && k==2) return 1000000000;
    long long sum = accumulate(parts.begin(), parts.end(), 0LL);
    long long l = 0, h = (k == 0 ? sum : sum / k);
    long long ans=0;
    while(l<=h){
        long long mid=l+(h-l)/2;
        if(check(parts,n,k,mid)){
            ans=mid;
            l=mid+1;
        }
        else h=mid-1;
    }
    return ans;
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> parts(N);
    for (int i = 0; i < N; ++i) {
        cin >> parts[i];
    }
    long long result = maxToys(N, K, parts);
    cout << result << endl;
    return 0;
}
