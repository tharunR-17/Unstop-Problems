#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    
    int n;
    long long k;
    cin >> n >> k;

    vector<long long> budget(n);

    for (int i = 0; i < n; i++) {
        cin >> budget[i];
    }

    int left = 0;
    long long sum = 0;
    int cnt = 0;

    for (int right = 0; right < n; right++) {

        sum += budget[right];

        while (sum > k) {
            sum -= budget[left];
            left++;
        }

        cnt = max(cnt, right - left + 1);
    }

    cout << cnt;

    return 0;
}
