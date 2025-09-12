#include <iostream>
#include <vector>

using namespace std;

// Placeholder for user logic function
int minOperationsToNonNegative(int n, int k, vector<int>& A) {
    // User should implement their logic here
    // Parameters:
    //     n (int): Number of elements in the array
    //     k (int): Integer K as described in the problem statement
    //     A (vector<int>): Array of integers (-1, 0, 1)
    // Returns:
    //     int: Minimum number of operations required to make the array non-negative, or -1 if impossible
    int ans = 0;
    vector<int> cnt(n+2, 0);
    for(int i=1;i<=n-k+1;i++){
        cnt[i] += cnt[i-1];
        A[i-1] = A[i-1] * ((cnt[i]%2)?-1:1);
        if(A[i-1]==-1){
            A[i-1]= 1;
            cnt[i]+=1;
            if(i+k<=n)cnt[i+k]-=1;
            ans += 1;
        }
    }

    for(int i=n-k+2;i<=n;i++){
        cnt[i] += cnt[i-1];
        A[i-1] = A[i-1] * ((cnt[i]%2)?-1:1);
        if(A[i-1]==-1){
            return -1;
        }
    }

    return ans;
    // return 0; // Placeholder return value
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    
    // Call the user logic function and print the result
    int result = minOperationsToNonNegative(n, k, A);
    cout << result << endl;
    
    return 0;
}
