#include <bits/stdc++.h>
using namespace std;

int max_disjoint_alliances(int n, int m, int t, std::vector<int> &a, std::vector<int> &b) {
    // Write your logic here.
    int ans=0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int i=0, j=0;
    while (i<n && j<m){
        if (a[i]<b[j] && a[i]+b[j]<=t){
            ans++;
            i++;
            j++;
        }
        else{
            j++;
        }
    }
    return ans;
}

int main() {
    int n, m, t;
    std::cin >> n >> m >> t;
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    int result = max_disjoint_alliances(n, m, t, a, b);
    std::cout << result << std::endl;

    return 0;
}
