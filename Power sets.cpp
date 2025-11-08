#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> ans;

void solve(vector<int>& nums, int i, vector<int> temp) {

    if(i == nums.size()) {
        ans.push_back(temp);
        return;
    }

    solve(nums, i+1, temp);
    temp.push_back(nums[i]);
    solve(nums, i+1, temp);
}
void subsets(vector<int> &nums) {
    vector<int> temp;
    solve(nums, 0, temp);
}

int main() {

    int n;
    cin>>n;
    vector<int> nums(n);
    for(auto &i : nums) cin>>i;

    subsets(nums);

    for(auto &i : ans) {
        for(auto &j : i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }   
    return 0;
}
