#include <iostream>
#include <cmath>
using namespace std;

int find(int m) {
    if (m == 0) return 0;
    return (int) sqrt(m);  // count of perfect squares ≤ m
}

int main() {
    int m;
    cin >> m;
    int count = find(m);
    cout << count << endl;
    return 0;
}
