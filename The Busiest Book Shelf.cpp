#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
    int N;
    cin >> N;

    unordered_map<long long, int> freq;

    long long ans = 0;
    int maxFreq = 0;

    for (int i = 0; i < N; i++) {
        long long id;
        cin >> id;

        freq[id]++;

        if (freq[id] > maxFreq) {
            maxFreq = freq[id];
            ans = id;
        } 
        else if (freq[id] == maxFreq && id < ans) {
            ans = id;
        }
    }

    cout << ans;

    return 0;
}
