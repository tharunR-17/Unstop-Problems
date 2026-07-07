#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;

    long long prev2 = 0, prev1 = 0;

    for (int i = 0; i < N; i++) {
        long long x;
        cin >> x;

        long long curr = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = curr;
    }

    cout << prev1;

    return 0;
}
