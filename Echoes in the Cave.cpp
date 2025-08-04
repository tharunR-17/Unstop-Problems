#include <iostream>
#include <vector>

using namespace std;

// Function where user will write the logic
// Parameters: N (number of chambers), E (energy levels)
// Returns: Minimum total cost to travel or -1 if not possible
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Recursive function to find the minimum cost from `index` to the last chamber
int solve(int index, vector<int>& E, vector<int>& dp)
{
    int N = E.size();
    if(index == N - 1) 
        return 0; // Reached the last chamber

    if(dp[index] != -1) 
        return dp[index];

    int minCost = INT_MAX;
    for(int j = index + 1; j < N; j++)
    {
        if(E[j] > E[index])
        {
            int jumpCost = (j - index) * (j - index);
            int subCost = solve(j, E, dp);
            if(subCost != INT_MAX)
                minCost = min(minCost, jumpCost + subCost);
        }
    }

    return dp[index] = minCost;
}
int minimumCostToTravel(int N, vector<int>& E)
{
    vector<int> dp(N, -1);
    int result = solve(0, E, dp); // Start from index 0 (i.e., chamber 1)

    return (result == INT_MAX) ? -1 : result;
}


int main() {
    int N;
    cin >> N;
    
    vector<int> E(N);
    for (int i = 0; i < N; ++i) {
        cin >> E[i];
    }
    
    // Call the user logic function
    int result = minimumCostToTravel(N, E);
    
    // Print the result
    cout << result << endl;
    
    return 0;
}
