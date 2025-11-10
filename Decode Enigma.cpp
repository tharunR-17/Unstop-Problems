#include<bits/stdc++.h>

using namespace std;




    string interpret(string s) {

        string ans;

        for (int i = 0; i < s.size(); ) {

            if (s[i] == 'S') ans += "send ", ++i;

            else if (s[i + 1] == ']') ans += "the ", i += 2;

            else ans += "ships ", i += 5;

        }

        return ans;

    }

void solve()

{

  string n; cin>>n;

  cout<<interpret(n);

}

signed main(){

            ios_base::sync_with_stdio(false);

    // cin.tie(NULL);

    // #ifndef ONLINE_JUDGE

    // freopen("IO files/Basic_input (3).txt", "r", stdin);

    // freopen("IO files/Basic_output (3).txt", "w", stdout);

    // #endif

    solve();

   

    return 0;

}
