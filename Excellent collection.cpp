#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define _io ios_base::sync_with_stdio(false); cin.tie(NULL);

string solve(ll n, vector<ll> arr)
{
    return "YES";
}

int main()
{
    _io;
    ll T;
    cin >> T;
    while (T--)
    {
        ll n;
        cin >> n;
        vector<ll> arr(n);
        for (ll i = 0; i < n; ++i)
        {
            cin >> arr[i];
        }
        cout << solve(n, arr) << endl;
    }
    return 0;
}
