#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

int find_missing_number(vector<int>& arr, int n) {
    // Write your logic here.
    int cnt=1;
    sort(arr.begin(),arr.end());
    for(int i=0;i<n;i++){
        if(arr[i]==cnt)cnt++;
    }
    return cnt;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n-1);
    for(int i = 0; i < n-1; i++) {
        cin >> arr[i];
    }

    int result = find_missing_number(arr, n);
    cout << result << endl;

    return 0;
}
