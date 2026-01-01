#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> capacity(N), initial(N);
    for (int i = 0; i < N; ++i) cin >> capacity[i];
    for (int i = 0; i < N; ++i) cin >> initial[i];
    int lossPercent;
    cin >> lossPercent;

    vector<double> water(N);
    for (int i = 0; i < N; ++i) water[i] = initial[i];

    for (int i = 0; i < N - 1; ++i) {
        double available = min(water[i], (double)capacity[i]);
        double sent = available;

        double lost = ceil(sent * lossPercent / 100.0);
        double received = sent - lost;

        double canReceive = min(received, (double)(capacity[i + 1] - water[i + 1]));
        water[i + 1] += canReceive;
        water[i] -= sent;
    }

    cout << (int)water[N - 1] << endl;
    return 0;
}
