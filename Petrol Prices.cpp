#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n;
    cin>>n;

    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];

    stack<int> s;
    vector<int> next(n,n);
    for(int i=0;i<n;i++){

        if(s.empty()||a[s.top()]>=a[i]){
            s.push(i);
        }else{
            while(!s.empty() && a[s.top()]<a[i]){

                next[s.top()]=i;
                s.pop();

            }
            s.push(i);
        }

    }

    for(int i=0;i<n;i++){

        if(next[i]==n){
            cout<<0<<" ";
            continue;
        }

        cout<<next[i]-i<<" ";

    }

    return 0;
}
