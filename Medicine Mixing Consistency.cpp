#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long minEnergyCost(const vector<int>& temp, int max_diff) 
{
    int n=temp.size();
    if(n<=1) return 0;

    vector<int> current=temp;

    for (int i=1; i<n;++i) {
        if (current[i]>current[i-1]+max_diff) 
        {
            current[i]=current[i-1]+max_diff;
        }
    }

    for(int i=n-2;i>=0;--i)
    {
        if(current[i]>current[i+1]+max_diff)
        {
            current[i]=current[i+1]+max_diff;
        }
    }

    long long total_cost=0;
    for(int i=0;i<n;++i)
    {
        total_cost+=(long long)temp[i]-current[i];
    }

    return total_cost;
}

int main()
{
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> temp(n);
    for (int i = 0; i < n; ++i) {
        cin >> temp[i];
    }

    cout << minEnergyCost(temp, k) << endl;

    return 0;
}
