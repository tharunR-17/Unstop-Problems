#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<string, int> memo;

int dfs(int i, int lastFruit, const vector<int>& F) {
    if (i >= (int)F.size()) return 0;
    string key = to_string(i) + "," + to_string(lastFruit);
    if (memo.count(key)) return memo[key];
    int take = 0;
    if (F[i] != lastFruit) {
        take = 1 + dfs(i + 1, F[i], F);
    }
    int skip = dfs(i + 2, lastFruit, F);
    int result = max(take, skip);
    memo[key] = result;
    return result;
}

int maxFruits(int n, const vector<int>& F) {
    memo.clear();
    return dfs(0, -1, F);
}

int main() {
    int n;
    cin >> n;
    vector<int> F(n);
    for (int i = 0; i < n; ++i) {
        cin >> F[i];
    }
    cout << maxFruits(n, F) << endl;
    return 0;
}
