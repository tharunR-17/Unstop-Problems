#include <cmath>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
     int n,k;
     cin>>n>>k;
     vector<int>a(n);
     for(int i=0;i<n;i++){
       cin>>a[i];
     }
     priority_queue<int>pq;
     for(int i=0;i<n;i++){
       pq.push(a[i]);

     }
     k--;
     while(k--){
       pq.pop();

     }
     cout<<pq.top()<<endl;
    return 0;
}
