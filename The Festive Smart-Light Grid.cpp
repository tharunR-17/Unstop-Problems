#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    vector<bool> present(100001, false);

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        if (x != -1)
            present[x] = true;
    }

    for (int d = 1; K - d > 0 && K + d <= 100000; d++) {
        int x = K - d;
        int y = K + d;

        if (present[x] && present[y]) {
            cout << x << " " << y;
            return 0;
        }
    }

    cout << -1;

    return 0;
}
