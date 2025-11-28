#include <bits/stdc++.h>
using namespace std;

struct Box {
    int l, w, h, wt;
};

// Sort by base area (l × w) descending
bool cmp(const Box &a, const Box &b) {
    return (a.l * a.w) > (b.l * b.w);
}

int max_height_of_stack(int n, vector<vector<int>>& boxes) {
    vector<Box> all;

    // Generate all rotations
    for (int i = 0; i < n; i++) {
        int h = boxes[i][0], w = boxes[i][1], l = boxes[i][2], wt = boxes[i][3];

        all.push_back({l, w, h, wt});
        all.push_back({w, h, l, wt});
        all.push_back({h, l, w, wt});
    }

    // Sort boxes by base area in descending order
    sort(all.begin(), all.end(), cmp);

    int size = all.size();
    vector<int> dp(size);

    int ans = 0;
    for (int i = 0; i < size; i++) {
        dp[i] = all[i].h; // start with height of this box alone
        for (int j = 0; j < i; j++) {
            if (all[i].l < all[j].l && all[i].w < all[j].w && all[i].wt < all[j].wt) {
                dp[i] = max(dp[i], dp[j] + all[i].h);
            }
        }
        ans = max(ans, dp[i]);
    }

    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> boxes(n, vector<int>(4));

    for (int i = 0; i < n; i++) {
        cin >> boxes[i][0] >> boxes[i][1] >> boxes[i][2] >> boxes[i][3];
    }

    cout << max_height_of_stack(n, boxes) << "\n";
    return 0;
}
