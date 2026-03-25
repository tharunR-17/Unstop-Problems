#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int compute_maximum_spi_sum(const vector<vector<int>>& spi_matrix) 
{
    int n = spi_matrix.size();
    
    vector<int> dp(1<<n,0);

    
    for(int mask=0;mask<(1<<n);++mask) 
    {
    
        int assigned_shops=0;
        for(int i=0;i<n;i++) 
        {
            if((mask>>i)&1) assigned_shops++;
        }


        if(assigned_shops==n) break;

        
        for(int j=0;j<n;j++)
        {
            if(!((mask>>j)&1))
            {
                int next_mask=mask | (1<<j);
                dp[next_mask]=max(dp[next_mask],dp[mask]+spi_matrix[assigned_shops][j]);
            }
        }
    }

    
    return dp[(1<<n)-1];
}

int main() {
    int N;
    cin >> N;
    vector<vector<int>> spi_matrix(N, vector<int>(N));

    for(int i=0;i<N;++i) 
    {
        for(int j=0;j<N;++j)
        {
            cin >> spi_matrix[i][j];
        }
    }

   
    int result = compute_maximum_spi_sum(spi_matrix);
    cout << result << endl;

    return 0;
}
