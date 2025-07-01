#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// User logic function placeholder
int target;
int diff;
int n;
long long ans=0;
long long fact(int num){
    long long ft=1;
    while(num>0){
        ft*=(long long)(num);
        num--;
    }
    return ft;
}
void check(int ind,vector<int> &arr,int sum,unordered_map<int,int> mp){
    if(sum==target){
        long long cnt=0;
        long long ft=1;
        for(auto it:mp){
            int temp=it.second;
            cnt+=(long long)temp;
            ft*=fact(temp);
        }
        if(cnt>1){
            ans+=fact(cnt)/ft;
        }
        return;
    }
    if(ind>=n || sum>target)return;
    for(int i=ind+1;i<n;i++){
        if(abs(arr[ind]-arr[i])>=diff ){
            mp[arr[i]]++;
            check(i,arr,sum+arr[i],mp);
            mp[arr[i]]--;
            if(mp[arr[i]]==0)mp.erase(arr[i]);
        }
    }
}
int count_valid_permutations(vector<int> arr, int t, int d) {
    // User needs to implement this function
    // Use the parameters A (array of integers), T, and D
    // Return the number of valid permutations
    n=arr.size();
    target=t;
    diff=d;
    ans=0;
    unordered_map<int,int> mp;    
    for(int i=0;i<n;i++){
        mp[arr[i]]++;
        check(i,arr,arr[i],mp);
        mp.erase(arr[i]);
    }
    return ans;
}

int main() {
    int N, T, D;
    std::cin >> N >> T >> D;
    
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    
    // Call the user logic function and print the result
    int result = count_valid_permutations(A, T, D);
    std::cout << result << std::endl;
    
    return 0;
}
