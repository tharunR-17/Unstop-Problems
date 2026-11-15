#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    long long lo, hi;
    cin >> lo >> hi;

    priority_queue<long long> leftHeap;
    priority_queue<long long, vector<long long>, greater<long long>> rightHeap;

    leftHeap.push(lo);
    rightHeap.push(hi);

    long long minCost = 0;
    long long shiftLeft = 0;
    long long shiftRight = 0;

    for (int i = 2; i <= n; ++i) {
        long long up, down;
        cin >> lo >> hi >> up >> down;

        shiftLeft -= down;
        shiftRight += up;

        long long leftTop = leftHeap.top() + shiftLeft;
        long long rightTop = rightHeap.top() + shiftRight;

        if (lo > rightTop) {
            minCost += lo - rightTop;
            leftHeap.push(rightTop - shiftLeft);
            rightHeap.pop();
            rightHeap.push(lo - shiftRight);
            rightHeap.push(hi - shiftRight);
        } else if (hi < leftTop) {
            minCost += leftTop - hi;
            rightHeap.push(leftTop - shiftRight);
            leftHeap.pop();
            leftHeap.push(hi - shiftLeft);
            leftHeap.push(lo - shiftLeft);
        } else {
            leftHeap.push(lo - shiftLeft);
            rightHeap.push(hi - shiftRight);
        }
    }

    long long bestX = leftHeap.top() + shiftLeft;
    cout << minCost << " " << bestX << "\n";

    vector<long long> leftSlopes, rightSlopes;
    while (!leftHeap.empty()) {
        leftSlopes.push_back(leftHeap.top() + shiftLeft);
        leftHeap.pop();
    }
    reverse(leftSlopes.begin(), leftSlopes.end());

    while (!rightHeap.empty()) {
        rightSlopes.push_back(rightHeap.top() + shiftRight);
        rightHeap.pop();
    }

    int leftSize = leftSlopes.size();
    vector<long long> prefixLeft(leftSize + 1, 0);
    for (int i = 0; i < leftSize; ++i) {
        prefixLeft[i + 1] = prefixLeft[i] + leftSlopes[i];
    }

    int rightSize = rightSlopes.size();
    vector<long long> prefixRight(rightSize + 1, 0);
    for (int i = 0; i < rightSize; ++i) {
        prefixRight[i + 1] = prefixRight[i] + rightSlopes[i];
    }

    while (q--) {
        long long z;
        cin >> z;
        long long totalPenalty = minCost;
        if (z < leftSlopes.back()) {
            auto it = upper_bound(leftSlopes.begin(), leftSlopes.end(), z);
            int idx = it - leftSlopes.begin();
            long long slopeCount = leftSize - idx;
            long long slopeSum = prefixLeft[leftSize] - prefixLeft[idx];
            totalPenalty += slopeSum - slopeCount * z;
        } else if (z > rightSlopes.front()) {
            auto it = lower_bound(rightSlopes.begin(), rightSlopes.end(), z);
            int idx = it - rightSlopes.begin();
            long long slopeCount = idx;
            long long slopeSum = prefixRight[idx];
            totalPenalty += slopeCount * z - slopeSum;
        }
        cout << totalPenalty << "\n";
    }

    return 0;
}
