#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int maximizeTasks(vector<int>& energy, vector<int>& power){
    sort(energy.begin(),energy.end());
    sort(power.begin(),power.end());
    int n=energy.size(),m=power.size();
    int i=0,j=0;
    while(i<n && j<m){
        if(energy[i]<=power[j]){
            i++;
        }
        j++;
    }
    return i;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> energy(n);
    for (int i = 0; i < n; i++) {
        cin >> energy[i];
    }

    vector<int> power(m);
    for (int i = 0; i < m; i++) {
        cin >> power[i];
    }

    int maxTasks = maximizeTasks(energy, power);
    cout << maxTasks << endl;

    return 0;
}
