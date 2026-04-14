#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// User logic function
vector<int> processApplications(int N, int T, vector<vector<int>>& applications) {
    // User should implement the logic here.
    // This function should return a vector of integers where each integer
    // corresponds to the minimum number of checkpoints required for each application,
    // or -1 if it's not possible to meet or exceed T.
    vector<int> result;
    for(int t = 0; t < N; t++){
        sort(applications[t].begin(), applications[t].end(), greater<int>());
    }
    
    for(int t = 0; t < N; t++){
        int count = 0, sum = 0;
        for(int i = 0; i < applications[t].size(); i++){
            sum += applications[t][i];
            count++;
            if(sum >= T){
                result.push_back(count);
                break;
            }
        }
        if(sum < T){
            result.push_back(-1);
        }
    }

    return result; // Placeholder return
}

int main() {
    int N, T;
    cin >> N >> T;  // Read number of applications and required minimum total priority score

    vector<vector<int>> applications(N);  // To store all applications data

    for (int i = 0; i < N; ++i) {
        int C;
        cin >> C;  // Read number of checkpoints for the current application
        applications[i].resize(C);

        for (int j = 0; j < C; ++j) {
            cin >> applications[i][j];  // Read priority scores for each checkpoint
        }
    }

    // Call the user logic function
    vector<int> results = processApplications(N, T, applications);

    // Output the results
    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}
