#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class FenwickTree {
    int n;
    vector<int> bit;

public:
    FenwickTree(int size) : n(size), bit(size + 1, 0) {}

    void update(int index, int delta) {
        while (index <= n) {
            bit[index] += delta;
            index += index & -index;
        }
    }

    int query(int index) {
        int result = 0;

        while (index > 0) {
            result += bit[index];
            index -= index & -index;
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<int> type(M);
    vector<int> id(M);
    vector<int> value(M);
    vector<int> scores;

    for (int i = 0; i < M; i++) {
        cin >> type[i] >> id[i];

        if (type[i] == 1) {
            cin >> value[i];
            scores.push_back(value[i]);
        } else {
            value[i] = id[i];
        }
    }

    sort(scores.begin(), scores.end());

    scores.erase(
        unique(scores.begin(), scores.end()),
        scores.end()
    );

    FenwickTree fenwick(scores.size());

    unordered_map<int, int> activeBooks;

    for (int i = 0; i < M; i++) {
        if (type[i] == 1) {
            int bookId = id[i];
            int score = value[i];

            int index = lower_bound(
                scores.begin(), scores.end(), score
            ) - scores.begin() + 1;

            activeBooks[bookId] = score;
            fenwick.update(index, 1);
        }
        else if (type[i] == 2) {
            int bookId = id[i];
            int score = activeBooks[bookId];

            int index = lower_bound(
                scores.begin(), scores.end(), score
            ) - scores.begin() + 1;

            fenwick.update(index, -1);
            activeBooks.erase(bookId);
        }
        else {
            int threshold = id[i];

            int index = lower_bound(
                scores.begin(), scores.end(), threshold
            ) - scores.begin();

            cout << fenwick.query(index) << '\n';
        }
    }

    return 0;
}
