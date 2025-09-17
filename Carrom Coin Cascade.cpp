#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int get_max_score(int N, int sx, int sy, const vector<tuple<int, int, int>>& coins) {
    int max_score = 0;

    // Separate coins by direction
    vector<pair<int,int>> up, down, leftc, rightc; // {distance, value}

    for (auto &coin : coins) {
        int x, y, v;
        tie(x, y, v) = coin;

        if (x == sx && y > sy) { // Right
            rightc.push_back({y - sy, v});
        }
        else if (x == sx && y < sy) { // Left
            leftc.push_back({sy - y, v});
        }
        else if (y == sy && x < sx) { // Up
            up.push_back({sx - x, v});
        }
        else if (y == sy && x > sx) { // Down
            down.push_back({x - sx, v});
        }
    }

    // Sort by distance (closest first)
    auto process = [&](vector<pair<int,int>>& dir) {
        sort(dir.begin(), dir.end());
        if (dir.size() >= 2) {
            return dir[0].second + dir[1].second;
        }
        return 0;
    };

    max_score = max({process(up), process(down), process(leftc), process(rightc)});

    return max_score;
}

int main() {
    int N, sx, sy, M;
    cin >> N >> sx >> sy >> M;
    vector<tuple<int, int, int>> coins(M);
    for (int i = 0; i < M; ++i) {
        int x, y, v;
        cin >> x >> y >> v;
        coins[i] = make_tuple(x, y, v);
    }
    int result = get_max_score(N, sx, sy, coins);
    cout << result << endl;
    return 0;
}
