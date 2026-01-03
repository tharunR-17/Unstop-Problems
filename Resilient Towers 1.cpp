#include <bits/stdc++.h>
using namespace std;

int calculateRemainingTowers(int N, int K, int M, vector<int>& heights) {
    vector<int> stack;
    int skipsLeft = M;

    for (int i = 0; i < N; ++i) {
        int curr = heights[i];

        while (!stack.empty()) {
            int top = stack.back();
            int g = __gcd(top, curr); // Use __gcd instead of std::gcd

            if (g > K) {
                if (skipsLeft > 0) {
                    --skipsLeft;
                    break;
                } else {
                    curr += top;
                    stack.pop_back();
                }
            } else {
                break;
            }
        }

        stack.push_back(curr);
    }

    return stack.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K, M;
    cin >> N >> K >> M;

    vector<int> heights(N);
    for (int i = 0; i < N; ++i) {
        cin >> heights[i];
    }

    int result = calculateRemainingTowers(N, K, M, heights);
    cout << result << endl;

    return 0;
}
