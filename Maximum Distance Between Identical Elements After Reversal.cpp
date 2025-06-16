#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Function to be implemented by the user
int maxDistance(const vector<int>& arr) {
    /*
    Write your logic here.
    Parameters:
        arr (vector<int>): List of integers
    Returns:
        int: The maximum distance between two identical elements after one possible subarray reversal.
             If no two identical elements exist after the reversal, return -1.
    */
    unordered_map<int, int>st, lt ;
    int n = arr.size(), ans = 0;

    for(int i=0;i<n;i++){
        if(st.count(arr[i])){
            ans = max(ans, n-1 - st[arr[i]]);
        }else{
            st[arr[i]] =i;
        }
    }

    for(int i=n-1;i>=0;i--){
        if(lt.count(arr[i])){
            ans = max(ans, lt[arr[i]]);
        }else{
            lt[arr[i]] =i;
        }
    }
    return ans; // Placeholder return value
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n; // Read the size of the array

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i]; // Read the array elements
    }

    // Call the function to find the maximum distance between identical elements
    int result = maxDistance(arr);

    // Output the result
    cout << result << endl;

    return 0;
}
