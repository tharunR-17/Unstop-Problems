#include <iostream>
#include <vector>
using namespace std;

// User logic function
bool canWaterAllPlants(const vector<int>& W, int K, int R) {
    int jetsUsed = 1;  // start with first jet
    long long currentSum = 0;

    for (int water : W) {
        if (water > R) return false; // single plant exceeds jet capacity
        if (currentSum + water <= R) {
            currentSum += water;
        } else {
            jetsUsed++;
            currentSum = water;
            if (jetsUsed > K) return false;
        }
    }

    return jetsUsed <= K;
}

int main() {
    int N, K, R;
    cin >> N >> K;

    vector<int> W(N);
    for (int i = 0; i < N; ++i) {
        cin >> W[i];
    }

    cin >> R;

    bool result = canWaterAllPlants(W, K, R);

    if (result) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
