#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int maxTotalPopularity(const vector<int>& P, int N) {
    if (N == 0) return 0;
    

    long long prev2 = 0; 
    long long prev1 = 0; 
    
    for(int i=0; i<N;i++) 
    {
        long long current_val = max(0, P[i]);
        long long current_max = max(prev1, prev2 + current_val);
        prev2 = prev1;
        prev1 = current_max;
    }
    
    return (int)prev1;
}

int main() {
 

    int N;
    if (!(cin >> N)) return 0;

    vector<int> P(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }

    int result = maxTotalPopularity(P, N);
    cout << result << endl;

    return 0;
}
