#include <bits/stdc++.h>

using namespace std;

// Function prototype for user logic
vector<vector<int>>dp;
int calculateMaxHappiness(int N, int K,vector<int>& H);
int ans=0;
int rec(int i,int n,int k,vector<int>& h){
    if(k==0) return 0;
    if(i>=n){
        return -1e9;
    }
    if(dp[i][k]!=-1) return dp[i][k];
    //take
    int take=h[i]+rec(i+2,n,k-1,h);
    int notake=rec(i+1,n,k,h);
    return dp[i][k]=max(take,notake);
}
int main() {
    int N, K;
    cin >> N >> K;

    vector<int> H(N);
    for (int i = 0; i < N; ++i) {
        cin >> H[i];
    }
    
    // Call the user logic function
    int result = calculateMaxHappiness(N, K, H);

    // Print the result
    cout << result << endl;
    
    return 0;
}

// Function where the user will implement the logic
int calculateMaxHappiness(int N, int K,vector<int>& H) {
    dp.assign(N+1,vector<int>(K+1,-1));
    int ans=rec(0,N,K,H);
    return (ans<0)?-1:ans;
}
