#include <bits/stdc++.h>
#include <vector>

using namespace std;

  int maxJamun(int i,int n,vector<int> &nums,map<int,int>&m){
          if(i>n-1){
              return 0;
          }


          if(m.find(i)!=m.end()) return m[i];
          int pick = nums[i]+maxJamun(i+2,n,nums,m);
          int notpick=maxJamun(i+1,n,nums,m);


          m[i]=max(pick,notpick);
          return max(pick,notpick);
    }

int main() {
    vector<int> nums;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
      int a;
      cin>>a;
     nums.push_back(a);
    }
    map<int,int> m;
    cout << maxJamun(0,n,nums,m);
    return 0;
}
