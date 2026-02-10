#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    if (N == 0) {
        cout << 0;
        return 0;
    }

    int up = 1, down = 1;

    for (int i = 1; i < N; i++) {
        if (arr[i] > arr[i - 1]) {
            up = down + 1;
        } 
        else if (arr[i] < arr[i - 1]) {
            down = up + 1;
        }
        // equal elements are ignored
    }

    cout << max(up, down);
    return 0;
}
