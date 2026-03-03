#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    int N, K;
    cin >> N >> K;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = i + 1;
    }

    for (int op = 0; op < K; ++op) {
        vector<int> newArr;
        for (int i = 0; i < arr.size(); ++i) {
            if ((i % 3) != 0) {
                newArr.push_back(arr[i]);
            }
        }
        arr = newArr;
        if (arr.empty()) {
            break;
        }
    }

    long long sum = 0;
    for (int num : arr) {
        sum = (sum + num) % MOD;
    }

    cout << sum << endl;
    return 0;
}
