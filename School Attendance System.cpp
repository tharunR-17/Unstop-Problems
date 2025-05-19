#include<bits/stdc++.h>
using namespace std;

vector<int> user_logic(int n, vector<int>& arr) {
    // Write your logic here.
    // Parameters:
    //     n (int): Size of the array
    //     arr (vector<int>): Vector of integers representing elements of the array
    // Returns:
    //     vector<int>: Vector of roll numbers that are never called out until the end in sequential order
    vector<bool> call(n+1,false);
    for(int i=0;i<arr.size();i++){
        if(call[i+1]==false){
            call[arr[i]]=true;
        }
    }
    vector<int>ans;
    for(int i =1;i<=n;i++) if(!call[i]) ans.push_back(i);
    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> result = user_logic(n, arr);
    for (int i : result) {
        cout << i << " ";
    }
    return 0;
}
