#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n,k;
    cin>>n>>k;

    vector<int>a(n);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }  

    deque<int> dq;

    for (int i = 0; i < n; i++) {

        // Remove elements outside the current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Remove smaller elements from the back
        while (!dq.empty() && a[dq.back()] <= a[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Window is complete
        if (i >= k - 1) {
            cout << a[dq.front()];

            if (i < n - 1) {
                cout << " ";
            }
        }
    }

    cout << '\n';
    return 0;
}
