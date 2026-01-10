#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> P(N);
    for(int i = 0; i < N; i++) cin >> P[i];

    int count = 0;

    for(int i = 0; i < N; i++) {
        if(P[i] == 0) {
            bool left = (i > 0) && (P[i-1] == 1 || P[i-1] == 2);
            bool right = (i < N-1) && (P[i+1] == 1 || P[i+1] == 2);

            if(!left && !right) {
                // plant tree here
                P[i] = 1;
                count++;
            }
        }
    }

    cout << count << endl;
    return 0;
}
