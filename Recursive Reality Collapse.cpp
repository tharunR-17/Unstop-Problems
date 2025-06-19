#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int simulateCollapse(int nodes, int edges, int badCount, vector<int> &corrupted, vector<pair<int, int>> &rules) {
    vector<vector<int>> adjList(nodes);
    vector<int> inDegree(nodes, 0);

    for (auto &rule : rules) {
        int src = rule.first;
        int dst = rule.second;
        adjList[dst].push_back(src);
        ++inDegree[src];
    }

    vector<bool> flagged(nodes, false);
    queue<int> processing;
    for (int idx : corrupted) {
        if (inDegree[idx] == 0) {
            processing.push(idx);
            flagged[idx] = true;
        }
    }

    int result = 0;
    while (!processing.empty()) {
        int current = processing.front();
        processing.pop();
        ++result;

        for (int dependent : adjList[current]) {
            if (--inDegree[dependent] == 0 && !flagged[dependent]) {
                flagged[dependent] = true;
                processing.push(dependent);
            }
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> unstableRealities(k);
    for (int i = 0; i < k; ++i) {
        cin >> unstableRealities[i];
    }

    vector<pair<int, int>> constraints(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        constraints[i] = {a, b};
    }

    cout << simulateCollapse(n, m, k, unstableRealities, constraints) << '\n';
    return 0;
}
