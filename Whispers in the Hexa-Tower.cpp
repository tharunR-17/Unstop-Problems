#include <bits/stdc++.h>
using namespace std;

int whispers_in_hexa_tower(int N, int M, int K, vector<int>& rune_list, vector<pair<int,int>>& edges) {
    int total_chambers = 6 * N;
    vector<vector<int>> graph(total_chambers);
    unordered_map<int, int> rune_index;
    for (int i = 0; i < K; i++) {
        rune_index[rune_list[i]] = i;
    }

    for (auto& e : edges) {
        graph[e.first].push_back(e.second);
        graph[e.second].push_back(e.first);
    }

    int start = 0;
    int exit_node = total_chambers - 1;
    int full_mask = (1 << K) - 1;

    vector<vector<bool>> visited(total_chambers, vector<bool>(1 << K, false));
    queue<tuple<int,int,int>> q;

    int init_mask = 0;
    if (rune_index.count(start)) {
        init_mask |= (1 << rune_index[start]);
    }

    q.emplace(start, init_mask, 0);
    visited[start][init_mask] = true;

    while (!q.empty()) {
        auto [node, mask, steps] = q.front();
        q.pop();

        if (node == exit_node && mask == full_mask) {
            return steps;
        }

        for (int nei : graph[node]) {
            int new_mask = mask;
            if (rune_index.count(nei)) {
                int bit = rune_index[nei];
                if ((mask & (1 << bit)) != 0) {
                    continue; // already visited this rune
                }
                new_mask |= (1 << bit);
            }
            if (!visited[nei][new_mask]) {
                visited[nei][new_mask] = true;
                q.emplace(nei, new_mask, steps + 1);
            }
        }
    }

    return -1;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<int> rune_list(K);
    for (int i = 0; i < K; ++i) {
        cin >> rune_list[i];
    }

    vector<pair<int, int>> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    int result = whispers_in_hexa_tower(N, M, K, rune_list, edges);
    cout << result << endl;

    return 0;
}
