#include <bits/stdc++.h>
using namespace std;

void user_logic(int n, vector<int>& enemy_groups, int m) {
    /*
    Write your logic here.
    Parameters:
        n (int): Number of groups of enemies
        enemy_groups (vector<int>&): Vector of integers representing the number of enemies in each group
        m (int): Number of minutes Jack has before the enemies activate their shield
    Returns:
        Minimum integer K and its octal representation as a string
    */

    long long l=1, r=accumulate(enemy_groups.begin(), enemy_groups.end(), 0ll), ans=-1;

    auto find = [&](long long md){
        long long cnt = 0;
        for(int i : enemy_groups){
            cnt += (i+md-1)/md;
        }
        return cnt<=(long long)m;
    };

    auto octal = [&](long long n){
        unsigned long long res = 0, pVal=1;
        while(n){
            res += pVal*(n%8);
            n/=8;
            pVal *= 10;
        }
        return res;
    };

    while(l<=r){
        long long md = l+(r-l)/2;
        if(find(md)){
            ans = md;
            r=md-1;
        }else{
            l=md+1;
        }
    }
    if(ans==-1){
        cout<<"1\n";
        return;
    }
    cout<<ans<<" "<<octal(ans);
}

int main() {
    int n, m;
    cin >> n;
    vector<int> enemy_groups(n);
    for (int i = 0; i < n; ++i) {
        cin >> enemy_groups[i];
    }
    cin >> m;
    
    user_logic(n, enemy_groups, m);
    
    return 0;
}J
