#include<bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
      int n;
    cin>>n;
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int t;
        cin>>t;
        mp[t]++;
    }
    priority_queue<int> pq;
    for (auto &it : mp) {
        pq.push(it.first);
    }

    int cnt = 0;
    while (!pq.empty()) {
        int elem = pq.top();
        pq.pop();
        if (mp[elem] > 1) {
            mp.erase(elem);
        } 
        else if (mp[elem] == 1) {
            cnt++;
            if ((elem / 2) != 0) {
                pq.push(elem / 2);
                mp[elem / 2]++;
            }
            mp.erase(elem);
        }
    }
    cout<<cnt<<endl;

    return 0;
    return 0;
}
