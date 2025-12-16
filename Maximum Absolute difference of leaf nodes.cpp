#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


TreeNode * create(vector<int> &arr,int level){
    if(arr.size()<=0 || level==0) return nullptr;
    TreeNode *root = new TreeNode(arr[0]);
    vector<int> left,right;
    for(int i=1;i<=arr.size()/2;i++){
        left.emplace_back(arr[i]);
    }
    for(int i=arr.size()/2+1;i<arr.size();i++){
        right.emplace_back(arr[i]);
    }
    root->left = create(left,level-1);
    root->right = create(right,level-1);
    return root;
}

// brute force
void dfs(TreeNode *root,int &mx,int &mn){
    if(!root) return;
    if(!root->left && !root->right){
        mx = max(root->val,mx);
        mn = min(root->val,mn);
    }
    if(root->left) dfs(root->left,mx,mn);
    if(root->right) dfs(root->right,mx,mn);
}
int maximumAbsDiff(TreeNode *root){
    if(!root) return 0;
    int mx=INT_MIN,mn = INT_MAX;
    dfs(root,mx,mn);
    return abs(mx-mn);
}

int main(){
    int t;cin>>t;
    while(t--){
        int numberOfLevel;cin>>numberOfLevel;
        int numberOfNodes = pow(2, numberOfLevel) - 1;
        vector<int> arr(numberOfNodes);
        for(int i=0;i<numberOfNodes;i++) cin>>arr[i];
        TreeNode *root = create(arr, numberOfLevel);
        cout<<maximumAbsDiff(root)<<"\n";
     }   
}
