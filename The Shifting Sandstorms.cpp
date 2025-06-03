#include <bits/stdc++.h>
using namespace std;

void compute_max_intensity_after_k_hours(int N, vector<int>& intensities, int K, vector<pair<int,int>>& queries) {
    // 1) Simulate K steps with integer division
    vector<int> curr = intensities, next(N);
    for(int t = 0; t < K; ++t) {
        if (N == 1) {
            next[0] = curr[0];
        } else {
            next[0]     = curr[1];
            next[N-1]   = curr[N-2];
            for(int i = 1; i < N-1; ++i) {
                next[i] = (curr[i-1] + curr[i+1]) / 2;
            }
        }
        curr.swap(next);
    }

    // 2) Precompute logs for RMQ
    vector<int> lg(N+1);
    lg[1] = 0;
    for(int i = 2; i <= N; ++i)
        lg[i] = lg[i/2] + 1;

    // 3) Build sparse table (max) on curr[]
    int P = lg[N];
    vector<vector<int>> st(P+1, vector<int>(N));
    for(int i = 0; i < N; ++i)
        st[0][i] = curr[i];
    for(int p = 1; p <= P; ++p) {
        int len  = 1 << p;
        int half = len >> 1;
        for(int i = 0; i + len <= N; ++i)
            st[p][i] = max(st[p-1][i], st[p-1][i+half]);
    }

    // 4) Answer each query in O(1)
    for(auto &qr : queries) {
        int l = qr.first - 1;
        int r = qr.second - 1;
        int len = r - l + 1;
        int p = lg[len];
        int ans = max(st[p][l], st[p][r - (1<<p) + 1]);
        cout << ans << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; 
    cin >> N;
    vector<int> intensities(N);
    for(int i = 0; i < N; ++i) 
        cin >> intensities[i];

    int K; 
    cin >> K;

    int Q; 
    cin >> Q;
    vector<pair<int,int>> queries(Q);
    for(int i = 0; i < Q; ++i)
        cin >> queries[i].first >> queries[i].second;

    compute_max_intensity_after_k_hours(N, intensities, K, queries);
    return 0;
}
