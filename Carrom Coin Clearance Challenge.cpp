#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int angle, maxAngle = 0;
    for (int i = 0; i < N; i++) {
        cin >> angle;
        if (angle > maxAngle)
            maxAngle = angle;
    }

    cout << maxAngle << endl;
    return 0;
}
