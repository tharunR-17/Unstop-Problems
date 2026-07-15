#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Optimize standard I/O operations for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> scores(n);
    for (int i = 0; i < n; ++i) {
        cin >> scores[i];
    }

    // Vector to store the active tail elements of increasing subsequences
    vector<int> tails;

    for (int x : scores) {
        // Find the first element in tails that is greater than or equal to x
        auto it = lower_bound(tails.begin(), tails.end(), x);

        if (it == tails.end()) {
            // If x is larger than all elements, it extends the longest subsequence
            tails.push_back(x);
        } else {
            // Otherwise, replace the found element with x to maintain potential for a longer chain
            *it = x;
        }
    }

    // The size of the tails vector is the length of the Longest Increasing Subsequence
    cout << tails.size() << "\n";

    return 0;
}
