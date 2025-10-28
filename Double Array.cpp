#include <bits/stdc++.h>
using namespace std;

vector<int> concatenate(vector<int> &vec) {

    sort(vec.begin(), vec.end());

    vector<int> ans;

    for(int i=0; i<vec.size(); i++) {
        ans.push_back(vec[i]);
    }

    for(int i=0; i<vec.size(); i++) {
        ans.push_back(vec[i]);
    }

    return ans;
}

int main() {

    int n;
    cin>>n;

    vector<int> vec(n);
    for(auto &i : vec) cin>>i;

    vector<int> ans = concatenate(vec);

    for(int i=0; i<ans.size(); i++) cout<<ans[i]<<" ";   
    return 0;
}
