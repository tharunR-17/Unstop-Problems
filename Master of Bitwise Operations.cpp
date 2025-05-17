#include<bits/stdc++.h>
using  namespace std;
#define _io {ios_base::sync_with_stdio(false); cin.tie(0);}
typedef long long ll;
void solve()
{
    ll n,q;
    cin >> n >> q;

    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<vector<ll>> v(61,vector<ll>(n+1));

    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < 61; j++)
        {
            v[j][i+1] = v[j][i]+min(1LL,((1LL<<j)&a[i]));
        }

    }

    for (ll i = 0; i < q; i++)
    {
        ll k, l1 ,r1, l2, r2;
        cin >> k >> l1 >> r1 >> l2 >> r2;
        l1--;
        r1--;
        l2--;
        r2--;

        ll s1,u1,s2,u2;
        s1 = v[k][r1+1]-v[k][l1];
        s2 = v[k][r2+1]-v[k][l2];

        u1 = r1-l1+1-s1;
        u2 = r2-l2+1-s2;

        cout << (s1*u2) + (s2*u1) << "\n";
    }
}

int main()
{
    _io;
    ll T;
    cin>>T;
    while(T--){
        solve();
    }
}
