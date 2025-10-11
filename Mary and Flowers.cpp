#include <bits/stdc++.h>  
using namespace std;

int main() { 
    int n, t;                  
    cin >> n >> t;    // initializing the variables 
    vector<int> arr(n);   // initialize the input array
    int a = -1, b = -1;   // first and last variable 

    for(int i = 0; i < n; i++) { 
        cin >> arr[i]; 
    }  // filling the array 

    for(int i = 0; i < n - 1; i++) { 
        for(int j = i + 1; j < n; j++) { 
            if(arr[i] + arr[j] == t) {  
                a = i; 
                b = j; 
                break; 
            } 
        } 
        if(a != -1) break; 
    } 

    cout << a << " " << b;  // print the indexes
    return 0; 
}
