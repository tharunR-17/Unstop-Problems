#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int jump(vector<int>& nums) {
        int n = nums.size()-1;
        vector<int> dp(n+1, 10e5);
        dp[n] = 0;

        for(int i=n-1; i>=0; i--){
            for(int j=1; j<=nums[i] && i+j<=n; j++){
                dp[i] = min(dp[i], 1+dp[i+j]);
            }
        }

        return dp[0] == 10e5 ? -1 : dp[0];
    }
int main(){
    int n;
    cin>>n;
    vector<int> arr(n,0);
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    cout<<jump(arr)<<endl;
}
