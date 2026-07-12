#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_map<long long, int> mp;
    long long x;

    for (int i = 0; i < n; i++) {
        cin >> x;
        mp[x]++;
    }

    long long ans = 0;
    int mx = 0;

    for (auto &it : mp) {
        if (it.second > mx || (it.second == mx && it.first < ans)) {
            mx = it.second;
            ans = it.first;
        }
    }

    cout << ans << " " << mx;

    return 0;
}
