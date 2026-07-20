#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int main() {
    long long A, B;
    cin >> A >> B;

    long long lcm = (A / gcd(A, B)) * B;

    cout << lcm << endl;

    return 0;
}
