#include <bits/stdc++.h>
using namespace std;

int user_logic(int N, int M, int L, const vector<vector<vector<int>>>& warehouse) {
    int max_val = INT_MIN;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < L; ++k)
                max_val = max(max_val, warehouse[i][j][k]);
    return max_val;
}

int main() {
    int N, M, L;
    cin >> N >> M >> L;

    vector<vector<vector<int>>> warehouse(N, vector<vector<int>>(M, vector<int>(L)));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < L; k++) {
                cin >> warehouse[i][j][k];
            }
        }
    }

    int result = user_logic(N, M, L, warehouse);
    cout << result << endl;

    return 0;
}
