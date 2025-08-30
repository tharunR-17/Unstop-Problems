#include <bits/stdc++.h>
#include <vector>
using namespace std;

int min_k_bit_flips(vector<int>& arr, int k, int m) {
    // Write your logic here.
    // Parameters:
    //     arr: Binary array of integers (0s and 1s)
    //     k: Length of the subarray to flip
    //     m: Maximum number of flips allowed
    // Returns:
    //     int: Minimum number of flips required to make all elements 1 or -1 if not possible within M flips
    int curr=0, cnt=0;
    int n=arr.size();
    vector<int>v(n+1,0);
    for(int i=0;i<arr.size();i++){
        curr+=v[i];
        if((arr[i]+curr)%2==0){
            if(i+k>n)return -1;
            cnt++;
            if(cnt>m){
                return -1;
            }
            curr++;
            v[i+k]--;
        }
    }
    return cnt;
    return -1;
}

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Call user logic function and print the output
    int result = min_k_bit_flips(arr, k, m);
    cout << result << endl;
    return 0;
}
