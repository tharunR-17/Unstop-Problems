#include <bits/stdc++.h>
using namespace std;

int calculate_max_demand(int n, int k, vector<int>& demands, vector<vector<int>>& switch_costs) {
    int ans=0;
    ans+=demands[0];
    vector<int> v;
    for(int i=1; i<demands.size(); i++) v.push_back(demands[i]);
    sort(v.begin(), v.end(), greater<int> ());
    int i=0;
    while(k--) {ans+=v[i]; i++;}
    return ans;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> demands(n);
    for (int i = 0; i < n; i++) {
        cin >> demands[i];
    }
    vector<vector<int>> switch_costs(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> switch_costs[i][j];
        }
    }
    int result = calculate_max_demand(n, k, demands, switch_costs);
    cout << result << endl;
    return 0;
}
