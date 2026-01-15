#include <bits/stdc++.h>
using namespace std;

int main() {
    int M, N, T;
    cin >> M >> N >> T;

    int cells = M * N;
    int turns;

    if (M == 1 || N == 1)
        turns = 0;
    else
        turns = 2 * (M - 1);

    int total = cells + turns * T;
    cout << total << endl;
    return 0;
}
