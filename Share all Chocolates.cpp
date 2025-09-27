#include <iostream>
#include <vector>
using namespace std;

void can_partition_chocolates(int n, vector<int>& chocolates) {
    // Write your logic here.
    // Parameters:
    //     n (int): Number of bags
    //     chocolates (list): List of integers representing chocolates in each bag
    // Returns:
    //     str: "YES" or "NO" based on whether it's possible to divide chocolates equally
    int total=0;
    for(auto i:chocolates){
        total+=i;
    }
    if(total%2==1){
        cout<<"NO";
    }else{
        cout<<"YES";
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> chocolates(n);
    for (int i = 0; i < n; ++i) {
        cin >> chocolates[i];
    }
    can_partition_chocolates(n, chocolates);
    return 0;
}
