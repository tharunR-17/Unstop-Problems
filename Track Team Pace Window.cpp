#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    long long n,L;
    cin>>n>>L;

    vector<long long>a(n);

    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    deque<int>maxdq;
    deque<int>mindq;

    int i =0;
    int ans = 0;


    for(int j=0;j<n;j++){
        // Maintain decreasing deque for maximum
        while (!maxdq.empty() && a[maxdq.back()] <= a[j]) {
            maxdq.pop_back();
        }
        maxdq.push_back(j);


         // Maintain increasing deque for minimum
        while (!mindq.empty() && a[mindq.back()] >= a[j]) {
            mindq.pop_back();
        }
        mindq.push_back(j);


        // Shrink window if invalid
        while (a[maxdq.front()] - a[mindq.front()] > L) {

            if (maxdq.front() == i)
                maxdq.pop_front();

            if (mindq.front() == i)
                mindq.pop_front();

            i++;
        }
        ans = max(ans, j - i + 1);
    }
    cout<<ans<<endl;

    return 0;
}
