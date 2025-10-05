#include <iostream>
#include <vector>
#include <string>

using namespace std;

int count = 0;

void backtrack(const vector<int>& prices, int index, int currentSum, int selectedCount, int K, int L, int R) {
    if (selectedCount == K) {
        if (currentSum >= L && currentSum <= R) {
            count++;
        }
        return;
    }

    if (index >= prices.size() || selectedCount > K || currentSum > R)
        return;

    // Include current item
    backtrack(prices, index + 1, currentSum + prices[index], selectedCount + 1, K, L, R);

    // Exclude current item
    backtrack(prices, index + 1, currentSum, selectedCount, K, L, R);
}

int main() {
    int N, K, L, R;
    cin >> N >> K >> L >> R;

    vector<string> deviceTypes(N);
    vector<int> prices(N);

    for (int i = 0; i < N; ++i) {
        cin >> deviceTypes[i] >> prices[i];
    }

    backtrack(prices, 0, 0, 0, K, L, R);

    cout << count << endl;

    return 0;
}
