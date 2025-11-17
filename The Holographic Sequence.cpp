#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> memo;

int solve(const string& S, int i, int j) {
    if (i > j) {
        return 0;
    }
    
    if (i == j) {
        return 0;
    }
    
    if (memo[i][j] != -1) {
        return memo[i][j];
    }
    
    int result = 0;
    
    if (S[i] == S[j]) {
        result = max(2 + solve(S, i + 1, j - 1),
                     max(solve(S, i + 1, j),
                         solve(S, i, j - 1)));
                         
    } else {
        result = max(solve(S, i + 1, j), solve(S, i, j - 1));
    }
    
    memo[i][j] = result;
    return result;
}

int findLongestHolographicSubsequence(string S, int N) {
    if (N <= 5000) { 
        memo.assign(N, vector<int>(N, -1));
        return solve(S, 0, N - 1);
    }

    if (N == 0) return 0;
    
    vector<int> prev_row(N, 0);
    vector<int> curr_row(N, 0);
    
    for (int i = N - 1; i >= 0; --i) {
        for (int j = i + 1; j < N; ++j) {
            
            int ans = max(prev_row[j], curr_row[j-1]);
            
            if (S[i] == S[j]) {
                int pair_ans = 2 + prev_row[j-1];
                ans = max(ans, pair_ans);
            }
            curr_row[j] = ans;
        }
        prev_row = curr_row;
    }
    
    return prev_row[N - 1];
}

int main() {
    int N;
    string S;
    
    cin >> N >> S;
    
    int result = findLongestHolographicSubsequence(S, N);
    cout << result << endl;
    
    return 0;
}
