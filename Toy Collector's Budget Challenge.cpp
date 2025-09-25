#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calculateMaxFun(int N, int B, vector<int>& price, vector<int>& stock, vector<int>& fun) {
    struct Item {
        int cost;
        int value;
    };
    vector<Item> items;

    // Binary splitting of stock
    for (int i = 0; i < N; i++) {
        int count = stock[i];
        int base = 1;
        while (count > 0) {
            int take = min(base, count);
            items.push_back({price[i] * take, fun[i] * take});
            count -= take;
            base <<= 1;
        }
    }

    // Standard 0/1 Knapsack
    vector<int> dp(B + 1, 0);
    for (auto &it : items) {
        for (int b = B; b >= it.cost; b--) {
            dp[b] = max(dp[b], dp[b - it.cost] + it.value);
        }
    }

    return dp[B];
}

int main() {
    int N, B;
    cin >> N >> B;

    vector<int> price(N), stock(N), fun(N);
    for (int i = 0; i < N; i++) {
        cin >> price[i] >> stock[i] >> fun[i];
    }

    int maxFun = calculateMaxFun(N, B, price, stock, fun);
    cout << maxFun << endl;
    return 0;
}
